#pragma once
#include <imgui.h>
#include <string>
#include <imgui_stdlib.h>
#include <ostream>

namespace ImStructs {

    typedef int CanvasFlags;
    auto const CanvasFlags_None = 0;
    auto const CanvasFlags_Clicked = 1 << 0;
    auto const CanvasFlags_Delete = 1 << 1;
    //auto const CanvasFlags_MoveUp = 1 << 2; legacy we use drag and drop now
    //auto const CanvasFlags_MoveDown = 1 << 3;
    
    struct ImStruct
    {
        ImStruct() = default;
        virtual ~ImStruct() = default;
        
        std::string label = "default";
        CanvasFlags canvasFlags = CanvasFlags_None;

        float width = 0.0f;
        
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
            ImGui::DragFloat("Width", &width, 0, 500);
            if(ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Width (only on some components) using ImGui::SetNextItemWidth(width)");
            }
        }

        virtual std::string Compile()
        {
            if(width != 0.0f) {
                return "ImGui::SetNextItemWidth(" + std::to_string(width) + "); ";
            }
            return "";
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

        std::string Compile() override
        {
            return ImStruct::Compile() + "ImGui::TextUnformatted(\"" + text + "\");";
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

        std::string Compile() override
        {
            std::string buttonCall = "";
            if(size.x != 0.0f && size.y != 0.0f) {
                buttonCall = "ImGui::Button(\"" + label + "\", ImVec2(" + std::to_string(size.x) + ", " + std::to_string(size.y) + "))";
            }
            buttonCall = "ImGui::Button(\"" + label + "\")";
            
            return ImStruct::Compile() + "if(" + buttonCall + ") { /** TODO: Add code for " + label + " **/ }"; /** hej chris **/
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

        std::string Compile() override
        {
            return ImStruct::Compile() + "ImGui::InputText(\"" + label + "\", &" + label + "buf, " + std::to_string(flags) + ", " + std::to_string((long long)callback) + ", " + std::to_string((long long)user_data) + ");";
        }
    };
}
