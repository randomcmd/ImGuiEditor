#pragma once
#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace ReMi {
    struct EditorSettings
    {
        std::string Theme = "Renewed Theme";
        
        std::map<std::string, bool> OpenWindows =
        {
            {"Hello World Window", true},
            {"Editor Window", true},
            {"Component Window", true},
            {"Compile Window", true},
            {"Debug Window", false},
            {"Canvas", true},
            {"Component Tree Window", true},
            {"Hello World Window", true}
        };

        std::vector<std::filesystem::path> LastOpenedProjects = { R"(resources\Sample Save Files\defaults_smol_brother.lay)" };
        size_t MaxLastOpenedProjects = 10;

        void AddProjectOpen(std::filesystem::path path);

        bool SettingsWindow(EditorSettings* out_settings);

        // Categories
        void ThemeSettings();

        std::vector<std::string_view> SettingCategories =
        {
            "Theme"
        };

        void SaveToFile(const std::filesystem::path& path);
        void LoadFromFile(const std::filesystem::path& path);
    };
}
