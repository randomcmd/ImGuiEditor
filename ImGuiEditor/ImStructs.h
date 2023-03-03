#pragma once
#include <bitset>
#include <imgui.h>
#include <string>
#include <imgui_stdlib.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <ostream>

#include "CanvasData.h"

// #include "CanvasData.h"
class CanvasContainer;

namespace ImStructs {
    struct ImStructComponent;

    using CanvasFlags = int;
    auto constexpr CanvasFlags_None = 0;
    auto constexpr CanvasFlags_Clicked = 1 << 0;
    auto constexpr CanvasFlags_Delete = 1 << 1;

    using ComponentFlags = int;
    auto constexpr ComponentFlags_None = 0;
    auto constexpr ComponentFlags_SameLine = 1 << 0;
    auto constexpr ComponentFlags_OverridePosition = 1 << 1;

    struct ImStruct
    {
        std::string Label = "default"; const char* FallBackLabel = Label.c_str();       // Label used by some components also used as variable name for serialization
        std::string EditorLabel = "default";
        ReMi::Editor* ActiveIn = nullptr;                                               // Some components want to construct other components in the editor
        virtual void PreDraw() = 0;                                                     // Called before drawing the component for example to set the cursor position when using override position
        virtual void Cleanup() = 0;                                                     // Clean up any changes to the style stack or cursor here
        virtual void Draw() = 0;                                                        // Draw the component
        virtual void PostDraw() = 0;                                                    // After drawing the component in the editor things like state syncing or gizmos can be done here WARNING THIS WILL NOT BE COMPILED
        virtual void Editor() = 0;                                                      // Draw editor for component in a separate window created by Editor.cpp
        bool DrawReturn;                                                                // if draw returns a boolean then place it here
        CanvasFlags CanvasFlags = CanvasFlags_None;
        ComponentFlags ComponentFlags = ComponentFlags_None;
        [[nodiscard]] virtual std::string Serialise() const;
        virtual void Deserialise(const std::string str);
        virtual std::string Compile();
        virtual ~ImStruct() = default;
    };

    using ImStructUPtr =             std::unique_ptr<ImStruct>;
    using ImStructComponentUPtr =    std::unique_ptr<ImStructComponent>;
    using ScopedImStructUPtr =       std::unique_ptr<ScopedImStruct>;
    
    struct ImStructComponent : ImStruct
    {
        ImStructComponent() = default;
        ImStructComponent(const ImStructComponent& other) = default;
        ImStructComponent(ImStructComponent&& other) = default;
        ImStructComponent& operator=(const ImStructComponent& other) = default;
        ImStructComponent& operator=(ImStructComponent&& other) = default;
        ~ImStructComponent() override = default;

        void PreDraw() override;     
        void Cleanup() override;     
        void Draw() override;        
        void PostDraw() override;    
        void Editor() override;
        [[nodiscard]] std::string Serialise() const override;
        void Deserialise(std::string str) override;
        std::string Compile() override;

        float Width = 0.0f;                                                             // Override width of component using ImGui::SetNextItemWidth
        ImVec2 Position = ImVec2(0.0f, 0.0f);                                     // Override position of component using ImGui::SetCursorPos
        ImVec2 CursorTemp = ImVec2(0.0f, 0.0f);
        bool Held = false;
    };

    struct ScopedImStruct : ImStructComponent
    {
        std::string Name;
        ImStructUPtr Begin;
        CanvasContainer Canvas;
        ImStructUPtr End;
        bool CallEndOnlyIfBeginReturnsTrue = true;                                      // LEGACY REASONS SMH :triumph:
        
        ScopedImStruct(ImStructComponent* begin, ImStructComponent* end);
        void Draw() override;
        void Editor() override;
        void PreDraw() override;
        void PostDraw() override;
        void Cleanup() override;
        std::string Compile() override;
        [[nodiscard]] std::string Serialise() const override;
        void Deserialise(std::string str) override;
    };
    
    struct Text : ImStructComponent
    {
        std::string TextBuffer = "Hello, world!";

        void Draw() override
        {
            ImStructComponent::Draw();
            ImGui::TextUnformatted(TextBuffer.c_str());
        }

        void Editor() override
        {
            ImStructComponent::Editor();
            ImGui::InputText("Text", &TextBuffer);
        }

        std::string Compile() override
        {
            return ImStructComponent::Compile() + "ImGui::TextUnformatted(\"" + TextBuffer + "\");";
        }
    };

    struct Button : ImStructComponent
    {
        ImVec2 size;

        void Draw() override
        {
            ImStructComponent::Draw();
            ImGui::Button(Label.c_str(), size);
        }

        void Editor() override
        {
            ImStructComponent::Editor();
            ImGui::InputFloat2("Size", (float*)&size);
        }

        std::string Compile() override
        {
            std::string buttonCall;
            if(size.x != 0.0f || size.y != 0.0f) {
                buttonCall = "ImGui::Button(\"" + Label + "\", ImVec2(" + std::to_string(size.x) + ", " + std::to_string(size.y) + "))";
            }
            else {
                buttonCall = "ImGui::Button(\"" + Label + "\")"; // Removes optional parameter
            }
            
            return ImStructComponent::Compile() + "if(" + buttonCall + ") { /** TODO: Add code for " + Label + " **/ }"; /** hej chris **/
        }
    };

    struct InputText : ImStructComponent // how to add hot reloading to chrome? a: in the serttings 
    {
        std::string buf;
        ImGuiInputTextFlags flags = 0;
        ImGuiInputTextCallback callback = nullptr;
        void* user_data = nullptr;

        void Draw() override
        {
            ImStructComponent::Draw();
            ImGui::InputText(Label.c_str(), &buf, flags, callback, user_data);
        }

        void Editor() override
        {
            ImStructComponent::Editor();
            ImGui::InputText("Buffer", &buf);
        }

        std::string Compile() override
        {
            return ImStructComponent::Compile() + "ImGui::InputText(\"" + Label + "\", &" + Label + "buf, " + std::to_string(flags) + ", " + std::to_string((long long)callback) + ", " + std::to_string((long long)user_data) + ");";
        }
    };
    
    template <typename T>
    void EditorHelper(const std::string_view label, T)
    {
        ImGui::Button("Type Not Implemented!");
        // add hover tooltip with type name
        const auto type = typeid(T).name();
        if(ImGui::IsItemHovered())
        {
            const auto tooltip = std::string(type) + " " + std::string(label);
            ImGui::SetTooltip(tooltip.c_str());
        }
    }

    template <> 
    inline void EditorHelper(const std::string_view label, int** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::InputInt(label.data(), *pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, float** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::InputFloat(label.data(), *pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, std::string** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::InputText(label.data(), *pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, const char** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::InputText(label.data(), (char*) *pointer, 256, ImGuiInputTextFlags_ReadOnly); // ImGuiInputTextFlags_ReadOnly assures const is not violated  // NOLINT(clang-diagnostic-cast-qual)
        ImGui::PopID();
    }

    template <>
    inline void EditorHelper(const std::string_view label, bool** pointer)
    {
        ImGui::PushID(pointer);
        ImGui::Checkbox(label.data(), *pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, ImVec2* pointer)
    {
        ImGui::PushID(pointer);
        ImGui::DragFloat2(label.data(), (float*)pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, ImColor* pointer)
    {
        ImGui::PushID(pointer);
        ImGui::ColorEdit4(label.data(), (float*)pointer);
        ImGui::PopID();
    }
}
