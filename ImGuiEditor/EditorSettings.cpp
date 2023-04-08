#include "EditorSettings.h"

#include "FileDialog.h"
#include "imgui.h"
#include "ImSerialise.h"

void ReMi::EditorSettings::AddProjectOpen(std::filesystem::path path)
{
    std::erase(LastOpenedProjects, path); // remove path and push it to the top if it already exists
    LastOpenedProjects.insert(LastOpenedProjects.begin(), path);
    if(LastOpenedProjects.size() > MaxLastOpenedProjects) // Only keeps track of the last MaxLastOpenedProjects projects
    {
        LastOpenedProjects.erase(LastOpenedProjects.begin());
    }
}

bool ReMi::EditorSettings::SettingsWindow(EditorSettings* out_settings)
{
    const auto window_size = ImGui::GetContentRegionAvail();
    const float settings_height = window_size.y - 30;
    
    ImGui::BeginChild("Setting Categories", ImVec2(window_size.x * 0.2f, settings_height), true);
    static std::string_view selected_category = SettingCategories[0];
    for(auto category : SettingCategories)
    {
        if(ImGui::Selectable(category.data(), selected_category == category))
        {
            selected_category = category;
        }
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("Settings", ImVec2(0, settings_height), true);
    if(selected_category == "Theme")
    {
        ThemeSettings();
    }
    ImGui::EndChild();
    
    // push a blue color for the button
    ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_Tab]);

    ImGui::SetCursorPosX(window_size.x - 85);
    if(ImGui::Button("Save"))
    {
        if (out_settings) {
            *out_settings = *this;
        }
        ImGui::CloseCurrentPopup();
        return true;
    }
    ImGui::PopStyleColor();

    ImGui::SameLine();
    if(ImGui::Button("Cancel"))
    {
        selected_category = SettingCategories[0];
        if (out_settings)
        {
            *out_settings = {};
        }
        ImGui::CloseCurrentPopup();
    }
                
    ImGui::EndPopup();
    return false;
}

void ReMi::EditorSettings::ThemeSettings()
{
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Theme: ");
    ImGui::SameLine();
    const std::vector<std::string_view> themes = {"Renewed Theme", "Visual Studio Theme", "ImGui Theme", "ImGui Light Theme", "ImGui Classic Theme"};
    if(ImGui::BeginCombo("##Theme Combo", Theme.data()))
    {
        for(const auto& theme : themes)
        {
            if(ImGui::Selectable(theme.data(), Theme == theme))
            {
               Theme = theme;
            }
        }
        ImGui::EndCombo();
    }
}

void ReMi::EditorSettings::SaveToFile(const std::filesystem::path& path)
{
    ImSerialisation::Call theme_call{"Theme", {Theme}};
    FileSystem::WriteFile(path, theme_call.string() + ";");
}

void ReMi::EditorSettings::LoadFromFile(const std::filesystem::path& path)
{
    const ImSerialisation::Call theme_call{FileSystem::ReadFile(path)}; 
    Theme = theme_call.Params[0];
}
