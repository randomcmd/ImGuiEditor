#pragma once
#include <imgui.h>
#include <string>
#include <imgui_stdlib.h>

namespace ImStructs {

    typedef int CanvasFlags;
    auto const CanvasFlags_None = 0;
    auto const CanvasFlags_Clicked = 1 << 0;
    auto const CanvasFlags_Delete = 1 << 1;
    auto const CanvasFlags_MoveUp = 1 << 2;
    auto const CanvasFlags_MoveDown = 1 << 3;
    
    struct ImStruct
    {
        ImStruct() = default;
        virtual ~ImStruct() = default;
        
        std::string label = "default";
        CanvasFlags canvasFlags = CanvasFlags_None;
        
        virtual void Draw() = 0;
        virtual void Editor()
        {
            ImGui::TextUnformatted(label.c_str());
            ImGui::InputText("Label", &label);
            ImGui::SameLine();
            if(ImGui::Button("X"))
            {
                canvasFlags &= ~CanvasFlags_Clicked;
            }
            ImGui::SameLine();
            if(ImGui::Button("DELETE"))
            {
                canvasFlags |= CanvasFlags_Delete;
            }
            if(label.length() == 0)
            {
                label = "default";
            }
        }
    };
    
    struct Text : ImStruct
    {
        std::string text;

        void Draw() override
        {
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
            ImGui::InputText(label.c_str(), &buf, flags, callback, user_data);
        }

        void Editor() override
        {
            ImStruct::Editor();
            ImGui::InputText("Buffer", &buf);
        }
    };
}