#include "Editor.h"

#include <string>
#include <vector>

void ReMi::EditorWindow()
{
    ImGui::Begin("Hello, world!");

    static bool demo = false;
    ImGui::Checkbox("Demo", &demo);
    if (demo)
    {
        ImGui::ShowDemoWindow(&demo);
    }
    
    ImGui::Button("Button");
    // Our buttons are both drag sources and drag targets here!
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
    {
        int n = 39;
        ImGui::SetDragDropPayload("EDITOR_NEW_BUTTON", &n, sizeof(int));
        ImGui::Text("This is a drag and drop source");
        ImGui::EndDragDropSource();
    }
    
    ImGui::End();
}

void ReMi::Canvas()
{
    ImGui::Begin("Canvas");
    static std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    static ImVec2 cursorPos;
    static ImVec2 mousePos;
    static bool sameLine = false;
    static bool previewButton = false;
    
    for (auto number : numbers)
    {
        if(number == 69)
        {
            ImGui::SameLine();
            continue;
        }
        
        ImGui::Button(std::to_string(number).c_str());
        cursorPos = ImGui::GetCursorScreenPos();
        mousePos = ImGui::GetMousePos();
    }

    sameLine = mousePos.y < cursorPos.y;

    if(sameLine)
    {
        ImGui::SameLine();
    }
    
    ImGui::Button("Reciever");
    
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("EDITOR_NEW_BUTTON"))
        {
            IM_ASSERT(payload->DataSize == sizeof(int));

            if(sameLine)
            {
                numbers.push_back(69);
                sameLine = false;
            }
            
            numbers.push_back(*(const int*)payload->Data);
        }
        else
        {
            ImGui::Text("new number hovering");
            previewButton = true;
        }
        ImGui::EndDragDropTarget();
    }
    
    ImGui::Text("Cursor Pos: %f, %f", cursorPos.x, cursorPos.y);
    ImGui::Text("Mouse Pos: %f, %f", mousePos.x, mousePos.y);
    ImGui::Text("Same Line: %s", sameLine ? "true" : "false");
    
    ImGui::End();
}