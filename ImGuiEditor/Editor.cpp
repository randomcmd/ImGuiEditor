#include "Editor.h"

#include <imgui.h>
#include <string>
#include <vector>
#include "ImGuiStructs.h"
CanvasContainer canvas;

void ReMi::EditorWindow()
{
    ImGui::Begin("Hello, world!");
    
    if(ImGui::Button("Add random text"))
    {
        canvas.m_ImStructs.push_back(new ImStructs::Text());
    }

    if(ImGui::BeginDragDropSource())
    {
        std::string payload = "Hello Sannej!";
        ImGui::SetDragDropPayload("component", new int(0), sizeof(int));
        ImGui::SetTooltip("addingg component");
        ImGui::EndDragDropSource();
    }
    
    if(ImGui::Button("Add random button"))
    {
        auto buttonData = new ImStructs::Button();
        buttonData->label = "hej button";
        canvas.m_ImStructs.push_back(buttonData);
    }

    if(ImGui::BeginDragDropSource())
    {
        std::string payload = "Hello Sannej!";
        ImGui::SetDragDropPayload("component", new int(1), sizeof(int));
        ImGui::SetTooltip("addingg component");
        ImGui::EndDragDropSource();
    }
    
    if(ImGui::Button("Add random input"))
    {
        auto inputTextData = new ImStructs::InputText();
        inputTextData->label = "hej user input";
        canvas.m_ImStructs.push_back(inputTextData);
    }

    if(ImGui::BeginDragDropSource())
    {
        std::string payload = "Hello Sannej!";
        ImGui::SetDragDropPayload("component", new int(2), sizeof(int));
        ImGui::SetTooltip("addingg component");
        ImGui::EndDragDropSource();
    }

    bool showingEditor = false;
    for (auto component : canvas.m_ImStructs)
    {
        if(component->clicked)
        {
            ImGui::Separator();
            ImGui::PushID(component);
            component->Editor();
            ImGui::PopID();
            showingEditor = true;
        }
        if(component->deleteComponent)
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

    if(canvas.m_ImStructs.empty())
    {
        if(CanvasDropTarget())
        {
            AddDropTargetToCanvas(0);
        };
    }
    
    // iterate through all the structs and draw them
    for(size_t i = 0; i < canvas.m_ImStructs.size(); i++)
    {
        auto component = canvas.m_ImStructs.at(i); 
        ImGui::PushID(component);
        component->Draw();
        ImGui::PopID();
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
        if(ImGui::IsItemClicked()) component->clicked = true;
        if(CanvasDropTarget())
        {
            AddDropTargetToCanvas(i + 1);
        }
    }
    
    ImGui::End();
}

bool ReMi::CanvasDropTarget()
{
    auto mouseCursorPos = ImGui::GetMousePos();
    auto cursorPos = ImGui::GetCursorScreenPos();
    if(abs(mouseCursorPos.y - cursorPos.y) > 10) return false;
    if(ImGui::GetDragDropPayload() == nullptr) return false;
    ImGui::BeginChild("addcomponent", ImVec2(100, 10));
    ImGui::EndChild();
    if(ImGui::BeginDragDropTarget())
    {
        ImGui::EndDragDropTarget();
        return true;
    }
    return false;
}

void ReMi::AddDropTargetToCanvas(size_t i)
{
    if(auto payload = ImGui::AcceptDragDropPayload("component")) {
        ImStructs::ImStruct* component;
        switch(*(int*)payload->Data)
        {
        case 0: component = new ImStructs::Text(); break;
        case 1: component = new ImStructs::Button(); break;
        default: component = new ImStructs::InputText();
        }
        auto iterator = canvas.m_ImStructs.begin() + static_cast<long long>(i);
        canvas.m_ImStructs.insert(iterator, component);
    }
}
