#include "Editor.h"

// All functions used by the Plugin API will be put here to avoid having the Plugin API depend on all of the Editor class

[[nodiscard]] ImStructUPtr ReMi::Editor::TemporaryConstructFromName(const std::string& name) const
{
    for(const auto& [component_map_name, component_map] : m_ComponentMaps) {
        for(auto& [component_factory_name, component_factory] : component_map) {
            const auto function_name = component_factory_name.substr(component_factory_name.find_last_of("##") + 1);
            if(name == function_name) {
                return ImStructUPtr((*component_factory)());
            }
        }
    }
    return {};
}

size_t ReMi::Editor::ComponentID()
{
    return m_LastComponentID++;
}