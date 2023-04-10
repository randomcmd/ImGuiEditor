#pragma once
#include <filesystem>
#include <iostream>
#include <Windows.h>

#include "../ImStructs.h"

using ComponentMap = std::unordered_map<std::string, const ImStructs::ImGuiComponentFactory*>;
using ComponentMaps = std::unordered_map<std::string, ComponentMap>;

static constexpr auto ADD_MAPS_TO_HASH = false;

class Plugin
{
public:
    struct PluginSpecs
    {
        std::string Name;
        std::string Version;
        std::string Author;
        std::string Description;
        std::string Github;
    } PluginSpecs;

    ComponentMaps ComponentMaps;

    [[nodiscard]] size_t Hash() const
    {
        size_t hash = 0;
        
        hash ^= std::hash<std::string>{}(PluginSpecs.Name);
        hash ^= std::hash<std::string>{}(PluginSpecs.Version);
        hash ^= std::hash<std::string>{}(PluginSpecs.Author);
        hash ^= std::hash<std::string>{}(PluginSpecs.Description);
        hash ^= std::hash<std::string>{}(PluginSpecs.Github);

        if constexpr (ADD_MAPS_TO_HASH) {
            for(auto& [key, value] : ComponentMaps)
            {
                hash ^= std::hash<std::string>{}(key);
                for(const auto& [inner_key, inner_value] : value)
                {
                    hash ^= std::hash<std::string>{}(inner_key);
                }
            }
        }

        return hash;
    }

    bool operator==(const Plugin& other) const
    {
        return Hash() == other.Hash();
    }
    
    static Plugin* LoadDLL(const std::filesystem::path path)
    {
        // load plugin from file
        const HMODULE h_module = LoadLibrary(path.c_str());
        if (h_module == nullptr)
        {
            std::cout << "Failed to load plugin: " << path << std::endl;
            return nullptr;
        }

        // get handle to create function -> Plugin* create()
        const auto create = reinterpret_cast<Plugin* (*)(ImGuiContext* context, ImGuiMemAllocFunc allocFunc, ImGuiMemFreeFunc freeFunc)>(
            GetProcAddress(h_module, "create")
        );

        ImGuiMemAllocFunc alloc_func;
        ImGuiMemFreeFunc free_func;
        void* user_data;
    
        ImGui::GetAllocatorFunctions(&alloc_func, &free_func, &user_data);
    
        return create(ImGui::GetCurrentContext(), alloc_func, free_func);
    }
};