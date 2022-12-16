#pragma once
#include <imgui.h>
#include <string>
#include <imgui_stdlib.h>
#include <iostream>
#include <ostream>

#include "ImGuiExtension.h"

namespace ImStructs {

    typedef int CanvasFlags;
    auto constexpr CanvasFlags_None = 0;
    auto constexpr CanvasFlags_Clicked = 1 << 0;
    auto constexpr CanvasFlags_Delete = 1 << 1;
    //auto const CanvasFlags_MoveUp = 1 << 2; legacy we use drag and drop now
    //auto const CanvasFlags_MoveDown = 1 << 3;

    typedef int ComponentFlags;
    auto constexpr ComponentFlags_None = 0;
    auto constexpr ComponentFlags_SameLine = 1 << 0;
    
    struct ImStruct
    {
        ImStruct() = default;
        virtual ~ImStruct() = default;
        
        std::string label = "default";
        const char* fallBackLabel = label.c_str();
        CanvasFlags canvasFlags = CanvasFlags_None;

        float width = 0.0f;
        
        virtual void Draw()
        {
            if(width != 0.0f) {
                ImGui::SetNextItemWidth(width);
            }
            fallBackLabel = label.c_str();
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
        ImVec2 size;

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
            if(size.x != 0.0f || size.y != 0.0f) {
                buttonCall = "ImGui::Button(\"" + label + "\", ImVec2(" + std::to_string(size.x) + ", " + std::to_string(size.y) + "))";
            }
            else {
                buttonCall = "ImGui::Button(\"" + label + "\")"; // Removes optional parameter
            }
            
            return ImStruct::Compile() + "if(" + buttonCall + ") { /** TODO: Add code for " + label + " **/ }"; /** hej chris **/
        }
    };

    struct InputText : ImStruct // how to add hot reloading to chrome? a: in the serttings 
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
    
    template <typename T>
    void EditorHelper(T not_implemented_type)
    {
        ImGui::Button("Type Not Implemented!");
        // add hover tooltip with type name
        auto type = typeid(not_implemented_type).name();
        if(ImGui::IsItemHovered())
        {
            ImGui::SetTooltip(type);
        }
    }

    template <>
    inline void EditorHelper(int** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::InputInt("Value", *pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(float** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::InputFloat("Value", *pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(std::string** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::InputText("Value", *pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const char** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::InputText("Const String Value", (char*) *pointer, 256, ImGuiInputTextFlags_ReadOnly); // ImGuiInputTextFlags_ReadOnly assures const is not violated
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(ImVec2* pointer)
    {
        ImGui::PushID(pointer);
        ImGui::DragFloat2("Value", (float*)pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(ImColor* pointer)
    {
        ImGui::PushID(pointer);
        ImGui::ColorEdit4("ImColor", (float*)pointer);
        ImGui::PopID();
    }
    
    template <typename F, typename... Args>
    class ComponentWrapper : public ImStruct
    {
    public:
        ComponentWrapper(F&& f, Args&&... args) : m_f(std::forward<F>(f)), m_args(std::forward<Args>(args)...)
        {
            // if the first argument is a c string, use it as the label
            // since the label is actually defined in ImStruct we point the first argument to the label
            // this is a bit hacky but it works (thanks copilot)
            if constexpr (std::is_same_v<const char*, std::decay_t<decltype(std::get<0>(m_args))>>) {
                std::get<0>(m_args) = fallBackLabel;
            }
        }

        void Draw() override
        {
            ImStruct::Draw();
            if constexpr (std::is_same_v<const char*, std::decay_t<decltype(std::get<0>(m_args))>>) {
                if(fallBackLabel)
                {
                    std::get<0>(m_args) = fallBackLabel;
                }
            }
            std::apply(m_f, m_args);
        }

        int apply()
        {
            return std::apply(m_f, m_args);
        }

        // print all the arguments and their types
        void Editor() override
        {
            ImStruct::Editor();

            // print all the arguments and their types
            std::apply([](auto&&... args) {
                (EditorHelper(&args), ...);
            }, m_args);

            using result_type = std::invoke_result_t<F, Args...>;
            // if result type is bool then create that as a button
            if constexpr (std::is_same_v<bool, result_type>) {
                ImGui::Button("Conditional Component");
            }
        }

        // write a destructor
        ~ComponentWrapper() override
        {
            ImStruct::~ImStruct();
            // call the destructors of the elements in the tuple
            std::apply([](auto&&... args) {
                (std::destroy_at(&args), ...);
            }, m_args);
        }

    private:
        F m_f;
        std::tuple<Args...> m_args;
    };

    template <typename F, typename... Args>
    ComponentWrapper<F, Args...>* make_component_wrapper(F&& f, Args&&... args)
    {
        return new ComponentWrapper<F, Args...>{std::forward<F>(f), std::forward<Args>(args)...};
    }
}