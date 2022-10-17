#include "Editor.h"

#include <string>
#include <vector>

#include "ImGuiStructs.h"

void ReMi::EditorWindow()
{
    ImGui::Begin("Hello, world!");

    static bool demo = false;
    ImGui::Checkbox("Demo", &demo);
    if (demo)
    {
        ImGui::ShowDemoWindow(&demo);
    }
    
    ImGui::End();
}

void ReMi::Canvas()
{
    ImGui::Begin("Canvas");
    std::vector<ImStructs::ImStruct*> ImGuiStructs;
    auto yay = new ImStructs::Text;
    yay->text = "Hello, purryaya!";
    ImGuiStructs.push_back(yay);
    
    // iterate through all the structs and draw them
    for (auto component : ImGuiStructs)
    {
        component->Draw();
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("This is a tooltip");
        if(ImGui::IsItemClicked()) component->clicked = true;
        if(component->clicked) component->Editor();
    }
    
    ImGui::End();
}