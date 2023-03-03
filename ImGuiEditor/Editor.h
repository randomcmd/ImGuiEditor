#pragma once
#include <functional>

#include "ComponentWrapper.h"

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
 * [0] Canvas data serialization
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
    public:
        void Render();
        void LoadPlugin(std::string_view path);
        [[nodiscard]] ImStructUPtr TemporaryConstructFromName(const std::string& name) const // TODO: Temporary because it doesn't take into consideration hash and potential revamp of plugin system
        {
            for(auto& [component_map_name, component_map] : m_ComponentMaps) {
                for(auto& [component_factory_name, component_factory] : component_map) {
                    if(component_factory_name.contains(name)) {
                        return ImStructUPtr((*component_factory)());
                    }
                }
            }
            return {};
        }
        
    private:
        void EditorWindow();
        void ComponentWindow(bool* open = nullptr);
        void CompileWindow() const;
        void SaveAndLoadWindow();
        void Canvas();
        void ComponentButton(std::string_view label, const ImStructs::ImGuiComponentFactory* factory);
        using ComponentMap = std::unordered_map<std::string, const ImStructs::ImGuiComponentFactory*>;
        using ComponentMaps = std::unordered_map<std::string, ComponentMap>;

        CanvasContainer     m_Canvas; // TODO(faraway): Have different editor windows have different canvases and states for editing of multiple guis at the same time
        ComponentMaps       m_ComponentMaps;
        ComponentMap        m_ComponentDict;
    };
    
    extern Editor* CurrentEditor(Editor* editor = nullptr);
}
