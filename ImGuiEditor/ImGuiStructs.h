#pragma once
#include <imgui.h>
#include <string>
#include <imgui_stdlib.h>

namespace ImStructs {

    struct ImStruct
    {
        bool clicked;
        virtual void Draw() = 0;
        virtual void Editor()
        {
            ImGui::Text("No Editor Implemented Yet");
        }
    };
    
    struct Text : ImStruct
    {
        std::string text;

        void Draw() override
        {
            ImGui::Text(text.c_str());
        }

        void Editor() override
        {
            ImGui::Text("Text");
            ImGui::InputText("Text", &text);
            
        }
    };

    struct Button : ImStruct
    {
        const char* label;
        const ImVec2 size;

        void Draw() override
        {
            ImGui::Button(label, size);
        }
    };

    struct InputText : ImStruct
    {
        const char* label;
        char* buf;
        size_t buf_size;
        ImGuiInputTextFlags flags = 0;
        ImGuiInputTextCallback callback = nullptr;
        void* user_data = nullptr;

        void Draw() override
        {
            ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
        }
    };
}