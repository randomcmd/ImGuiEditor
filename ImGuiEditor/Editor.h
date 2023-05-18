#pragma once
#include <functional>

#include "EditorSettings.h"
#include "imgui/FreeTypeTest.h"
#include "plugin/Plugin.h"

namespace ImStructs
{
    struct ScopedImStruct;
    struct ImStructComponent;
    struct ImStruct;
}

using ImStructUPtr =             std::unique_ptr<ImStructs::ImStruct>;
using ImStructComponentUPtr =    std::unique_ptr<ImStructs::ImStructComponent>;
using ScopedImStructUPtr =       std::unique_ptr<ImStructs::ScopedImStruct>;

/* Alpha 1.0 Feature List
 *
 * ImGuiEditor:
 * [1] Add basic GUI
 * [1] Viewports
 * [1] Docking
 * [1] Put everything into different windows
 * [1] Global component dict that can import components from dlls
 * [1] Implement basic dll loading as a proof of concept
 *  
 * Canvas:
 * [1] Basic canvas functionality
 * [1] Recursive canvases
 * [1] Canvas data
 * [0.9] Canvas data serialization TemporaryConstructFromName needs to be overhauled but not now pls
 *
 * Compilation (Honestly let's just rewrite a lot of the compilation system itself in the canvas):
 * [0] Compilation errors on label collision -> having two labels with the same name and giving an option to add ## random number to the end of the label to avoid collision on this compile
 * [0] Add buffers as variables properly -> new string turns into static auto buffer = new std::string("Buffer") -> this also enables buffer content to be set from the start!
 *
 * Component Editor:
 * [1] Basic component editor functionality
 * [1] Recursive component editor
 *
 * Templates:
 * [1] Template compilation
 * [1] Template parameter naming
 *
 * UI Overhaul:
 * [1] New color palette
 * [1] Top navigation bar -> Opening projects, settings other stuff
 * [1] Better Tree View + Put method into ImStruct
 * [0.5] Plugin UI
 * [0] Better component editor
 * [1] Save and load
 * [0] Compilation
 * [0] New Component window that can also shows all the components
 * [0] Component Search
 * [1] Editable Theme?
 * [1] Improved drag and drop (I don't have a piss kink remove the yellow pls)
 * [0] Improved override position? Snap to grid? Implement in ImStructComponent only?
 * [0.99] Better font and emotes pls I want pensive :pensive:
 * [1] Hello World Window
 * [1] Settings Window and Saving
 * [1] Opening Files and Plugins and Saving Files
 * [1] Integrate Editor Label
 * [0] Error API
 *
 * General Code Style and Feature Usage:
 * [1] Abolish raw pointers
 *
 * Bugs:
 * [0] NO BUGS YET HIHI :cool:
 */

namespace ReMi
{
    class Editor
    {
    public: // Backend API to render editor
        Editor();
        
        void PreNewFrame();
        void Render();
        
        // Editor Plugin API
        [[nodiscard]] ImStructUPtr TemporaryConstructFromName(const std::string& name) const; // TODO: Temporary because it doesn't take into consideration hash and potential revamp of plugin system
        size_t ComponentID();

        // Temporary fix for native ImGui Style Editor
        static constexpr bool override_color_scheme = true;

    private:
        // Windows
        void HelloWorldWindow();
        void EditorWindow();
        void ComponentWindow(bool* open = nullptr);
        void CompileWindow() const;
        void ComponentTreeWindow() const;
        void SaveAndLoadWindow();
        void DebugWindow();
        void RightClickMenu();
        void VoidWindow();
        void Canvas();

        // Private API
        void LoadPlugin(std::filesystem::path path);
        void UnloadPlugin(Plugin& plugin);
        void OpenProjectFromPath(std::filesystem::path path);
        
        void ComponentButton(std::string_view label, const ImStructs::ImGuiComponentFactory* factory);
        
        using ComponentMap = std::unordered_map<std::string, const ImStructs::ImGuiComponentFactory*>;
        using ComponentMaps = std::unordered_map<std::string, ComponentMap>;

        CanvasContainer     m_Canvas; // TODO(faraway): Have different editor windows have different canvases and states for editing of multiple guis at the same time
        ComponentMaps       m_ComponentMaps;
        ComponentMap        m_ComponentDict;

        std::vector<std::unique_ptr<Plugin>> m_LoadedPlugins;
        
        EditorSettings      m_EditorSettings;
        void ApplySettings();

        ImGuiStyle          m_ImGuiStyle;
        FreeTypeTest        m_FreeTypeTest;

        size_t             m_LastComponentID = 1;
    };
}
