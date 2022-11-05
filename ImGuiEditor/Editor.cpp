#include "Editor.h"
#include <string>
#include <vector>

#include "ImGuiStructs.h"
CanvasContainer canvas;

void ReMi::EditorWindow()
{
    ImGui::Begin("Hello, world!");
    
    if(ImGui::Button("Add random text"))
    {
        auto textData = new ImStructs::Text();
        textData->text = "Hello, world!";
        canvas.m_ImStructs.push_back(textData);
    }
    
    if(ImGui::Button("Add random button"))
    {
        auto buttonData = new ImStructs::Button();
        buttonData->label = "hej button";
        canvas.m_ImStructs.push_back(buttonData);
    }
    
    if(ImGui::Button("Add random input"))
    {
        auto inputTextData = new ImStructs::InputText();
        inputTextData->label = "hej user input";
        canvas.m_ImStructs.push_back(inputTextData);
    }

    bool showingEditor = false;
    for (auto component : canvas.m_ImStructs)
    {
        if(component->canvasFlags & ImStructs::CanvasFlags_Clicked)
        {
            ImGui::Separator();
            ImGui::PushID(component);
            component->Editor();
            ImGui::PopID(); 
            showingEditor = true;
        }
        if(component->canvasFlags & ImStructs::CanvasFlags_Delete)
        {
            canvas.m_ImStructs.erase(std::remove(canvas.m_ImStructs.begin(), canvas.m_ImStructs.end(), component), canvas.m_ImStructs.end());
            delete component;
        }
    }

    if(showingEditor)
    {
        ImGui::Separator();
    }
    static bool demo = false;
    ImGui::Checkbox("Demo", &demo);
    if (demo)
    {
        ImGui::ShowDemoWindow(&demo);
    }
    
    // can i anchor a buttom to the bottom of the window? a: no q: WAIT WHAT? a: yes, but you have to do it manually
    //ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 35); // remi you just didn't put it in the right function smh you put it in the slider editor or something LMAO
    //ImGui::SetCursorPosY(20); the button doesn't render why? a: because the cursor is at the top of the window

    // how would i make that the button is anchored to the right side of the screen? a: you can't, you have to do it manually
    //ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 80); // remi you just didn't put it in the right function smh you put it in the slider editor or something LMAO
    
    ImGui::End();
}

void ReMi::Canvas()
{
    ImGui::Begin("Canvas");
    
    // iterate through all the structs and draw them
    for (auto component : canvas.m_ImStructs)
    {
        ImGui::PushID(component);
        component->Draw();
        ImGui::PopID();
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
        if(ImGui::IsItemClicked()) component->canvasFlags |= ImStructs::CanvasFlags_Clicked;
    }
    
    ImGui::End();
}