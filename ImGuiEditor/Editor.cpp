#include "Editor.h"

#include <functional>
#include "imgui.h"
#include <string>
#include <vector>

#include "FileDialog.h"
#include "ImStructs.h"
#include "ImGuiExtension.h"
#include "Target.h"
#include "backends/imgui_impl_opengl3.h"
#include "plugin/Plugin.h"

#define PREVIEW_LAST_COMPILE 1 // This is a temporary hack to import the compiled.cpp file

#if PREVIEW_LAST_COMPILE
#include "compiled.h"
#endif

using ImStructs::ImGuiComponentFactory;
using ImStructs::ImStructComponent;

ReMi::Editor::Editor()
{
    // TODO: TEMPORARY FIX
    static ImStructComponent editor_manager;
    editor_manager.ActiveIn = this;
    
    m_Canvas.ActiveIn = &editor_manager;
    m_EditorSettings.LoadFromFile("Settings.lay");
    ApplySettings();
    const auto default_plugin_path = "DefaultComponents.dll";
    LoadPlugin(default_plugin_path);
}

void ReMi::Editor::PreNewFrame()
{
    if(m_FreeTypeTest.PreNewFrame())
    {
        ImGui_ImplOpenGL3_DestroyDeviceObjects();
        ImGui_ImplOpenGL3_CreateDeviceObjects();
    }
}

void ReMi::Editor::Render()
{
    if(override_color_scheme)
    {
        ImGui::GetStyle() = m_ImGuiStyle;
    }
    VoidWindow();
    if(m_EditorSettings.OpenWindows["Editor Window"])
    {
        EditorWindow();
    }
    if(m_EditorSettings.OpenWindows["Component Window"])
    {
        ComponentWindow();
    }
    if(m_EditorSettings.OpenWindows["Debug Window"])
    {
        DebugWindow();
        SaveAndLoadWindow();
        m_FreeTypeTest.ShowFontsOptionsWindow();
    }
    if(m_EditorSettings.OpenWindows["Canvas"]) {
        Canvas();
    }
    if(override_color_scheme) {
        ImGui::GetStyle() = m_ImGuiStyle;
    }
    if(m_EditorSettings.OpenWindows["Component Tree Window"]) {
        ComponentTreeWindow();
    }
    if(m_EditorSettings.OpenWindows["Compile Window"]) {
        CompileWindow();
    }
    if(m_EditorSettings.OpenWindows["Hello World Window"])
    {
        HelloWorldWindow();
    }
}

void ReMi::Editor::DebugWindow()
{
    ImGui::Begin("All Powerful Debug");
    
    static bool demo = false;
    ImGui::Checkbox("Demo", &demo);
    if (demo)
    {
        ImGui::ShowDemoWindow(&demo);
    }

    if(ImGui::Button("Compile To File (Legacy)"))
    {
        m_Canvas.CompileCPP();
    }

#if PREVIEW_LAST_COMPILE
    static bool previewLastCompile = false;
    ImGui::SameLine();
    ImGui::Checkbox("Preview last compile", &previewLastCompile);
    if(previewLastCompile) {
        ImGui::Begin("Preview Last Compile");
        Gui();
        ImGui::End();
    }
#else
    ImGui::SameLine();
    ImGui::Text("Preview last compile is disabled");
#endif

    static bool ShowStyleEditor = false;
    ImGui::Checkbox("Style Editor", &ShowStyleEditor);
    // if (ShowStyleEditor && m_Canvas.m_ImGuiStyle.has_value())
    // {
    //     ImGui::Begin("Style Editor", &ShowStyleEditor);
    //     
    //     static ImGuiStyle style = m_Canvas.m_ImGuiStyle.value();
    //     static ImGuiStyle default_style = style;
    //     static bool always_apply = false;
    //     ReMi::StyleEditor(style);
    //     ImGui::Checkbox("Always Apply Style", &always_apply);
    //     if(always_apply || ImGui::Button("Apply Style"))
    //     {
    //         m_Canvas.m_ImGuiStyle = style;
    //     }
    //     if(ImGui::Button("Reset Style"))
    //     {
    //         m_Canvas.m_ImGuiStyle = default_style;
    //     }
    //     
    //     ImGui::End();
    // }
    
    ImGui::End();
}

void ReMi::Editor::RightClickMenu()
{
    ImGui::Button("=", ImVec2(24, 24));
    if(ImGui::IsItemHovered())
    {
        ImGui::SetTooltip("Main Menu");
    }

    const auto settings_popup_id = ImGui::GetID("Settings##Popup");
    
    if(ImGui::BeginPopupContextItem("Main Menu", ImGuiPopupFlags_MouseButtonLeft))
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New Project"))
            {
                m_Canvas.Clear();
                m_LastComponentID = 0;
            }
            if(ImGui::BeginMenu("Open Project"))
            {
                if(ImGui::MenuItem("Open Project"))
                {
                    OpenProjectFromPath(FileSystem::ShowOpenFileDialog());
                }
                ImGui::Separator();
                for(const auto& path : m_EditorSettings.LastOpenedProjects)
                {
                    const auto path_str = path.string();
                    if(ImGui::MenuItem(path_str.c_str()))
                    {
                        OpenProjectFromPath(path);
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if(ImGui::MenuItem("Save Project"))
            {
                const auto save_path = FileSystem::ShowSaveFileDialog("ImGuiEditorProject", "lay");
                const auto save_data = m_Canvas.Serialise();
                FileSystem::WriteFile(save_path, save_data);
            }
            ImGui::Separator();
            if(ImGui::MenuItem("Settings##Menu"))
            {
                ImGui::OpenPopup(settings_popup_id);
            }
            
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Project"))
        {
            if(ImGui::MenuItem("Load Plugin"))
            {
                const auto plugin_path = FileSystem::ShowOpenFileDialog();
                if(plugin_path.has_filename()) {
                    LoadPlugin(plugin_path);
                }
            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Windows"))
        {
            for(auto& [window, open] : m_EditorSettings.OpenWindows)
            {
                ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
                if(ImGui::MenuItem(window.c_str(), nullptr, &open))
                {
                    // open = !open; // you stupid twat this inverts the open twice so it just stays as it was before
                    // prevent the entire menu being closed
                }
                ImGui::PopItemFlag();
            }
            
            ImGui::EndMenu();
        }

        if(ImGui::MenuItem("Search for actions..."))
        {
            ImGui::Text("DUMMY");
        }
        
        ImGui::EndPopup();
    }

    // Always center this window when appearing
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    // change modal backround to be transparent
    ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, ImVec4(0, 0, 0, 0)); // TODO: This is a bug that could be reported
    ImGui::SetNextWindowSize(ImVec2(800, 600));

    bool open = true;
    if(ImGui::BeginPopupModal("Settings##Popup", &open, ImGuiWindowFlags_NoSavedSettings))
    {
        static auto unsaved_settings = m_EditorSettings;
        if(unsaved_settings.SettingsWindow(&m_EditorSettings))
        {
            ApplySettings();
        }
    }

    ImGui::PopStyleColor();
    
}

void ReMi::Editor::VoidWindow()
{
    // make the window transparent
    constexpr auto begin_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus;
    //constexpr auto begin_flags = 0; // uncomment this to make changes to the Void window
    ImGuiWindowClass window_class;
    window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
    ImGui::SetNextWindowClass(&window_class);
    const auto window_color = ImColor(32, 32, 32).Value;
    ImGui::PushStyleColor(ImGuiCol_WindowBg, window_color);
    ImGui::Begin("Void", nullptr, begin_flags);
    ImGui::PopStyleColor();
    RightClickMenu();
    ImGui::End();
}

void ReMi::Editor::LoadPlugin(std::filesystem::path path)
{
    Plugin* plugin = Plugin::LoadDLL(path);

    // if plugin already loaded, don't load it again
    for(const auto& already_loaded_plugin : m_LoadedPlugins)
    {
        if(*already_loaded_plugin == *plugin)
        {
            std::cout << "Plugin " << already_loaded_plugin->PluginSpecs.Name << "already loaded! Not reloading again!" << std::endl;
            return;
        }
    }
    
    for(auto& [name, plugin_map] : plugin->ComponentMaps) {
        std::string name_with_plugin_hash = name + "##" + std::to_string(plugin->Hash());
        m_ComponentMaps.insert({name_with_plugin_hash, plugin_map});
    }
    
    m_LoadedPlugins.emplace_back(plugin);
}

void ReMi::Editor::UnloadPlugin(Plugin& plugin)
{
    // iterate over all plugins and check if there is a matching plugin if yes delete it if no print error
    for(auto it = m_LoadedPlugins.begin(); it != m_LoadedPlugins.end(); ++it)
    {
        if(**it == plugin)
        {
            m_LoadedPlugins.erase(it);
            return;
        }
    }

    std::cout << "Plugin " << plugin.PluginSpecs.Name << " not found! Not unloading!" << std::endl;
}

void ReMi::Editor::OpenProjectFromPath(const std::filesystem::path path)
{
    if(path.empty()) return;
    m_LastComponentID = 0;
    m_Canvas.Deserialise(FileSystem::ReadFile(path), *this);
    m_EditorSettings.AddProjectOpen(path);
}

void ReMi::Editor::HelloWorldWindow()
{
    ImGui::Begin("Hello, world!", &m_EditorSettings.OpenWindows["Hello World Window"]);
    ImGui::Text("Hej Yan! Thanks for checking out my project! \nClick on The Cherno project to see a small introduction to the program!\nYou can also choose to create a new project!");
    ImGui::SeparatorText("Last Projects");
    for(const auto& path : m_EditorSettings.LastOpenedProjects)
    {
        if(ImGui::Button(path.filename().string().c_str()))
        {
            OpenProjectFromPath(path);
            m_EditorSettings.OpenWindows["Hello World Window"] = false;
        }
    }
    ImGui::SeparatorText("New Project");
    if(ImGui::Button("Create new project"))
    {
        m_Canvas.Clear();
        m_LastComponentID = 0;
        m_EditorSettings.OpenWindows["Hello World Window"] = false;
    }
    ImGui::SeparatorText("Tutorial");
    if(ImGui::Button("Open Tutorial"))
    {
        OpenProjectFromPath(R"(resources\Sample Save Files\tutorial.lay)");
        m_EditorSettings.OpenWindows["Hello World Window"] = false;
    }
    ImGui::End();
}

std::string LowerString(std::string_view string)
{
    std::string lower{string};
    std::ranges::transform(lower, lower.begin(), [](unsigned char c){ return std::tolower(c); });
    return lower;
}

void ReMi::Editor::EditorWindow()
{
    ImGui::Begin("Components");
    
    static std::string search;
    const bool use_search = !search.empty();
    const std::string search_normal = LowerString(search);
    
    
    //ImGui::SetNextItemWidth(-1);
    ImGui::SetCursorPosX(5);
    ImGui::InputTextWithHint("##search", "Search", &search);
    
    for (auto& [name, plugin_map] : m_ComponentMaps) {
        if(!use_search) {
            if(ImGui::CollapsingHeader(name.c_str())) {
                for (auto& [component_name, component_factory] : plugin_map)
                {
                    ComponentButton(component_name, component_factory);
                }
            }
            continue;
        }

        bool header = false;
        bool header_open = false;
        ImGui::PushID("using_search");
        for (auto& [component_name, component_factory] : plugin_map)
        {
            const std::string component_name_normal = LowerString(component_name);
            if(component_name_normal.find(search_normal) == std::string::npos) continue;
            if(!header)
            {
                ImGui::SetNextItemOpen(true);
                if(ImGui::CollapsingHeader(name.c_str()))
                {
                    header_open = true;
                }
                header = true;
            }
            if(header_open) {
                ComponentButton(component_name, component_factory);
            }
        }
        ImGui::PopID();
    }
    
    ImGui::End();
    ImGui::EndChild();
    
    // can i anchor a buttom to the bottom of the window? a: no q: WAIT WHAT? a: yes, but you have to do it manually
    //ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 35); // remi you just didn't put it in the right function smh you put it in the slider editor or something LMAO
    //ImGui::SetCursorPosY(20); the button doesn't render why? a: because the cursor is at the top of the window

    // how would i make that the button is anchored to the right side of the screen? a: you can't, you have to do it manually
    //ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 80); // remi you just didn't put it in the right function smh you put it in the slider editor or something LMAO
    
}

void ReMi::Editor::ComponentWindow(bool* open)
{
    ImGui::Begin("Selected Components", open);
    for (size_t i = 0; i < m_Canvas.ImStructs.size(); i++)
    {
        const auto& component = m_Canvas.ImStructs[i];
        if(component->CanvasFlags & ImStructs::CanvasFlags_Clicked)
        {
            ImGui::PushID(i);
            component->Editor();
            if(i != m_Canvas.ImStructs.size() - 1 && m_Canvas.ImStructs.at(i + 1)->CanvasFlags & ImStructs::CanvasFlags_Clicked)
            {
                ImGui::Separator();
            }
            ImGui::PopID();
        }
    }
    
    ImGui::End();
}

void ReMi::Editor::CompileWindow() const
{
    ImGui::Begin("Target Compiler");
    static std::string compiled;
    static Target::Target target;
    if(ImGui::Button("Compile"))
    {
        compiled = m_Canvas.Compile(&target);
    }
    ImGui::SameLine();
    if(ImGui::Button("Compile To File"))
    {
        const std::filesystem::path path = FileSystem::ShowSaveFileDialog("save", "lay");
        if(path.has_filename()) {
            FileSystem::WriteFile(path, m_Canvas.Compile(&target));
        }
    }
    ImGui::InputTextMultiline("##compiled", &compiled, ImVec2(-3, -3), ImGuiInputTextFlags_AllowTabInput);
    ImGui::End();
}

void ReMi::Editor::ComponentTreeWindow() const
{
    ImGui::Begin("Canvas Tree View");
    m_Canvas.DrawTree();
    ImGui::End();
}

void ReMi::Editor::SaveAndLoadWindow()
{
    ImGui::Begin("Serialisation");
    static std::string serialised;
    if(ImGui::Button("Serialise"))
    {
        serialised = m_Canvas.Serialise();
    }
    if(ImGui::Button("Deserialise"))
    {
        m_Canvas.Deserialise(serialised, *this);
    }
    if(ImGui::Button("Open File"))
    {
        OpenProjectFromPath(FileSystem::ShowOpenFileDialog());
    }
    ImGui::InputTextMultiline("##serialised", &serialised, ImVec2(-3, -3), ImGuiInputTextFlags_AllowTabInput);
    ImGui::End();
}

void ReMi::Editor::Canvas()
{
    ImGui::Begin("Canvas");
    m_Canvas.Draw();
    ImGui::End();
}

void ReMi::Editor::ComponentButton(std::string_view label, const ImGuiComponentFactory* factory)
{
    if(ImGui::Button(label.data()))
    {
        const auto component = factory->operator()();
        m_Canvas.AddComponent(ImStructUPtr(component));
    }
    if(ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("component", factory, sizeof(ImGuiComponentFactory));
        ImGui::SetTooltip("Adding %s", label.data());
        ImGui::EndDragDropSource();
    }
}

void ReMi::Editor::ApplySettings()
{
    if(m_EditorSettings.Theme == "Renewed Theme")
    {
        m_ImGuiStyle = ReMi::RenewedTheme();
    }
    if(m_EditorSettings.Theme == "Visual Studio Theme")
    {
        m_ImGuiStyle = ReMi::VisualStudioRounded();
    }
    if(m_EditorSettings.Theme == "ImGui Theme")
    {
        ImGui::StyleColorsDark(&m_ImGuiStyle);
    }
    if(m_EditorSettings.Theme == "ImGui Light Theme")
    {
        ImGui::StyleColorsLight(&m_ImGuiStyle);
    }
    if(m_EditorSettings.Theme == "ImGui Classic Theme")
    {
        ImGui::StyleColorsClassic(&m_ImGuiStyle);
    }

    m_EditorSettings.SaveToFile("Settings.lay");
}
