#include "Editor.h"

#include <functional>
#include "imgui.h"
#include <string>
#include <vector>

#include "ImStructs.h"
#include "ImGuiExtension.h"
#include "Target.h"
#include "plugin/Plugin.h"

#define PREVIEW_LAST_COMPILE 1 // This is a temporary hack to import the compiled.cpp file

#if PREVIEW_LAST_COMPILE
#include "compiled.h"
#endif

using ImStructs::ImGuiComponentFactory;
using ImStructs::ImStructComponent;

ReMi::Editor::Editor()
{
    m_ImGuiStyle = ReMi::VisualStudioRounded();
}

void ReMi::Editor::Render()
{
    if(override_color_scheme) {
        ImGui::GetStyle() = m_ImGuiStyle;
    }
    EditorWindow();
    ComponentWindow();
    Canvas();
    if(override_color_scheme) {
        ImGui::GetStyle() = m_ImGuiStyle;
    }
    m_Canvas.DrawTree();
    CompileWindow();
    SaveAndLoadWindow();
}

void ReMi::Editor::LoadPlugin(const std::string_view path)
{
    const Plugin* default_plugin = Plugin::LoadDLL(path);
    for(auto& [name, plugin_map] : default_plugin->ComponentMaps) {
        std::string name_with_plugin_hash = name + "##" + std::to_string(default_plugin->Hash());
        m_ComponentMaps.insert({name_with_plugin_hash, plugin_map});
    }
}

void ReMi::Editor::EditorWindow()
{
    ImGui::Begin("Hello, world!");
    ImGui::BeginChild("ComponentWindows");

    // make child dockable
    auto id = ImGui::GetID("ComponentWindows");
    ImGui::DockSpace(id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    for (auto& [name, plugin_map] : m_ComponentMaps) {
        ImGui::Begin(name.c_str());
        for (auto& [name, component_factory] : plugin_map)
        {
            ComponentButton(name, component_factory);
        }
        ImGui::End();
    }

    ImGui::EndChild();
    
    // can i anchor a buttom to the bottom of the window? a: no q: WAIT WHAT? a: yes, but you have to do it manually
    //ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 35); // remi you just didn't put it in the right function smh you put it in the slider editor or something LMAO
    //ImGui::SetCursorPosY(20); the button doesn't render why? a: because the cursor is at the top of the window

    // how would i make that the button is anchored to the right side of the screen? a: you can't, you have to do it manually
    //ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 80); // remi you just didn't put it in the right function smh you put it in the slider editor or something LMAO

    ImGui::Begin("Misc");
    
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

    if(ImGui::Button("Compile To File (TargetV1)"))
    {
        static Target::Target target;
        m_Canvas.CompileToFile(&target, "compiled.cpp");
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
    if (ShowStyleEditor && m_Canvas.m_ImGuiStyle.has_value())
    {
        ImGui::Begin("Style Editor", &ShowStyleEditor);
        
        static ImGuiStyle style = m_Canvas.m_ImGuiStyle.value();
        static ImGuiStyle default_style = style;
        static bool always_apply = false;
        ReMi::StyleEditor(style);
        ImGui::Checkbox("Always Apply Style", &always_apply);
        if(always_apply || ImGui::Button("Apply Style"))
        {
            m_Canvas.m_ImGuiStyle = style;
        }
        if(ImGui::Button("Reset Style"))
        {
            m_Canvas.m_ImGuiStyle = default_style;
        }
        
        ImGui::End();
    }
    
    ImGui::End();
    ImGui::End();
}

void ReMi::Editor::ComponentWindow(bool* open)
{
    ImGui::Begin("Selected Components", open);
    for (size_t i = 0; i < m_Canvas.ImStructs.size(); i++)
    {
        auto& component = m_Canvas.ImStructs[i];
        if(component->CanvasFlags & ImStructs::CanvasFlags_Clicked)
        {
            ImGui::PushID(&component);
            component->Editor();
            ImGui::PopID();
        }
        if(component->CanvasFlags & ImStructs::CanvasFlags_Delete)
        {
            std::erase(m_Canvas.ImStructs, component);
        }
    }
    
    ImGui::End();
}

void ReMi::Editor::CompileWindow() const
{
    ImGui::Begin("Target Compiler");
    static std::string compiled;
    if(ImGui::Button("Compile With Target V1"))
    {
        static Target::Target target;
        compiled = m_Canvas.Compile(&target);
    }
    ImGui::InputTextMultiline("##compiled", &compiled, ImVec2(-3, -3), ImGuiInputTextFlags_AllowTabInput);
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
    ImGui::InputTextMultiline("##serialised", &serialised, ImVec2(-3, -3), ImGuiInputTextFlags_AllowTabInput);
    ImGui::End();
}

void ReMi::Editor::Canvas()
{
    ImGui::GetStyle() = m_Canvas.m_ImGuiStyle.value_or(ImGui::GetStyle());
    ImGui::Begin("Canvas");
    m_Canvas.Draw();
    ImGui::End();
}

void ReMi::Editor::ComponentButton(std::string_view label, const ImGuiComponentFactory* factory)
{
    static size_t id = 0;
    if(ImGui::Button(label.data())) // TODO: Maybe make this a colored button
    {
        m_Canvas.ImStructs.emplace_back(factory->operator()());                    // TODO: Better id system
        m_Canvas.ImStructs.back()->Label += std::format("##{}", id++);
    }
    if(ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("component", factory, sizeof(ImGuiComponentFactory));
        ImGui::SetTooltip("Adding %s", label.data());
        ImGui::EndDragDropSource();
    }
}
