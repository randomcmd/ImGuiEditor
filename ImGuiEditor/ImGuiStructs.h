#pragma once
#include <imgui.h>
#include <string>
#include <imgui_stdlib.h>

namespace ImStructs {

    struct ImStruct
    {
        std::string label = "default";
        bool clicked;
        bool deleteComponent;

        float width;
        
        virtual void Draw()
        {
            if(width != 0.0f) {
                ImGui::SetNextItemWidth(width);
            }
        }
        
        virtual void Editor()
        {
            ImGui::TextUnformatted(label.c_str());
            ImGui::InputText("Label", &label);
            ImGui::SameLine();
            if(ImGui::Button("X"))
            {
                clicked = false;
            }
            ImGui::SameLine();
            deleteComponent = ImGui::Button("DELETE");
            if(label.length() == 0)
            {
                label = "default";
            }
            ImGui::DragFloat("Width", &width, 0, 500);
            if(ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Width (only on some components) using ImGui::SetNextItemWidth(width)");
            }
        }
    };
    
    struct Text : ImStruct
    {
        std::string text = "Hello, world!";

        void Draw() override
        {
            ImStruct::Draw();
            ImGui::TextUnformatted(text.c_str());
        }

        void Editor() override
        {
            ImStruct::Editor();
            ImGui::InputText("Text", &text);
        }
    };

    struct Button : ImStruct
    {
        const ImVec2 size;

        void Draw() override
        {
            ImStruct::Draw();
            ImGui::Button(label.c_str(), size);
        }

        void Editor() override
        {
            ImStruct::Editor();
            ImGui::InputFloat2("Size", (float*)&size);
        }
    };

    struct InputText : ImStruct
    {
        std::string buf;
        ImGuiInputTextFlags flags = 0;
        ImGuiInputTextCallback callback = nullptr;
        void* user_data = nullptr;

        void Draw() override
        {
            ImStruct::Draw();
            ImGui::InputText(label.c_str(), &buf, flags, callback, user_data);
        }

        void Editor() override
        {
            ImStruct::Editor();
            ImGui::InputText("Buffer", &buf);
        }
    };
}