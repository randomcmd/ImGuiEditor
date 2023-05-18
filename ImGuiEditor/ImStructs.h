#pragma once
#include <bitset>
#include <string>
#include <functional>
#include "imgui.h"
#include "misc/cpp/imgui_stdlib.h"
#include "imgui_internal.h"

#include "CanvasData.h"
#include "ImString.h"

class ImString;

namespace ReMi
{
    class Editor;
}

namespace ImStructs
{
    struct ImStruct;
    struct ImStructComponent;
    struct ScopedImStruct;
    
    using ImStructUPtr =             std::unique_ptr<ImStruct>;
    using ImStructComponentUPtr =    std::unique_ptr<ImStructComponent>;
    using ScopedImStructUPtr =       std::unique_ptr<ScopedImStruct>;
    
    // Wrap make_component_wrapper in a ImGuiComponentFactory so that it can easily be saved in a dict for creation of that component
    using ImGuiComponentFactory = std::function<ImStruct*()>;
}

namespace ImStructs {
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
        virtual ~ImStruct() = default;
        
        std::string EditorLabel = "Default";                                            // Variable Name and internal label NOT USED BY COMPONENTS AS LABLE VALUE
        ReMi::Editor* ActiveIn = nullptr;                                               // Some components want to construct other components in the editor
        
        virtual void PreDraw() = 0;                                                     // Called before drawing the component for example to set the cursor position when using override position
        virtual void Cleanup() = 0;                                                     // Clean up any changes to the style stack or cursor here
        virtual void Draw() = 0;                                                        // Draw the component
        virtual void PostDraw() = 0;                                                    // After drawing the component in the editor things like state syncing or gizmos can be done here WARNING THIS WILL NOT BE COMPILED
        virtual void Editor() = 0;                                                      // Draw editor for component in a separate window created by Editor.cpp
        virtual void DrawTree() = 0;                                                    // Draw tree recursively for component in the editor
        
        bool DrawReturn;                                                                // if draw returns a boolean then place it here
        
        CanvasFlags CanvasFlags = CanvasFlags_None;
        ComponentFlags ComponentFlags = ComponentFlags_None;
        
        [[nodiscard]] virtual std::string Serialise() const;
        virtual void Deserialise(std::string str);
        virtual std::string Compile();
    };

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
        void DrawTree() override;
        [[nodiscard]] std::string Serialise() const override;
        void Deserialise(std::string str) override;
        std::string Compile() override;

        float Width = 0.0f;                                                             // Override width of component using ImGui::SetNextItemWidth
        ImVec2 Position = ImVec2(0.0f, 0.0f);                                     // Override position of component using ImGui::SetCursorPos
        ImVec2 CursorTemp = ImVec2(0.0f, 0.0f);
        bool Held = false;
        bool CustomClickBehaviour = false;
    };

    struct ScopedImStruct : ImStruct
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
        void DrawTree() override;
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
            if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
            if(ImGui::IsItemClicked()) CanvasFlags |= ImStructs::CanvasFlags_Clicked;
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
            ImGui::Button(EditorLabel.c_str(), size);
            if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
            if(ImGui::IsItemClicked()) CanvasFlags |= ImStructs::CanvasFlags_Clicked;
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
                buttonCall = "ImGui::Button(\"" + EditorLabel + "\", ImVec2(" + std::to_string(size.x) + ", " + std::to_string(size.y) + "))";
            }
            else {
                buttonCall = "ImGui::Button(\"" + EditorLabel + "\")"; // Removes optional parameter
            }
            
            return ImStructComponent::Compile() + "if(" + buttonCall + ") { /** TODO: Add code for " + EditorLabel + " **/ }"; /** hej chris **/
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
            ImGui::InputText(EditorLabel.c_str(), &buf, flags, callback, user_data);
            if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
            if(ImGui::IsItemClicked()) CanvasFlags |= ImStructs::CanvasFlags_Clicked;
        }

        void Editor() override
        {
            ImStructComponent::Editor();
            ImGui::InputText("Buffer", &buf);
        }

        std::string Compile() override
        {
            return ImStructComponent::Compile() + "ImGui::InputText(\"" + EditorLabel + "\", &" + EditorLabel + "buf, " + std::to_string(flags) + ", " + std::to_string((long long)callback) + ", " + std::to_string((long long)user_data) + ");";
        }
    };
    
    enum EditorHelperFlags {
        EditorHelperFlags_None = 0,
        EditorHelperFlags_Drag = 1 << 0,
        EditorHelperFlags_Slider = 1 << 1,
        EditorHelperFlags_Input = 1 << 3,
    };
    
    template <typename T>
    void EditorHelper(const std::string_view label, T, EditorHelperFlags flags = EditorHelperFlags_None)
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
    inline void EditorHelper(const std::string_view label, int** pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::InputInt(label.data(), *pointer);
        ImGui::PopID();
    }

    template <> 
    inline void EditorHelper(const std::string_view label, int* pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::InputInt(label.data(), pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, float** pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::InputFloat(label.data(), *pointer);
        ImGui::PopID();
    }

    template <>
    inline void EditorHelper(const std::string_view label, float* pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        if(flags & EditorHelperFlags_Drag)
        {
            ImGui::DragFloat(label.data(), pointer);
        }
        else if(flags & EditorHelperFlags_Slider)
        {
            ImGui::SliderFloat(label.data(), pointer, 0, 100, "%.3f", ImGuiSliderFlags_None);
        }
        else
        {
            ImGui::InputFloat(label.data(), pointer);
        }
        ImGui::PopID();
    }

    template <>
    inline void EditorHelper(const std::string_view label, ImString* pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::InputText(label.data(), pointer->StringPointer());
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, std::string** pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::InputText(label.data(), *pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, const char** pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::InputText(label.data(), (char*) *pointer, 256, ImGuiInputTextFlags_ReadOnly); // ImGuiInputTextFlags_ReadOnly assures const is not violated  // NOLINT(clang-diagnostic-cast-qual)
        ImGui::PopID();
    }

    template <>
    inline void EditorHelper(const std::string_view label, bool** pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::Checkbox(label.data(), *pointer);
        ImGui::PopID();
    }

    template <>
    inline void EditorHelper(const std::string_view label, bool* pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::Checkbox(label.data(), pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, ImVec2* pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::DragFloat2(label.data(), (float*)pointer);
        ImGui::PopID();
    }
    
    template <>
    inline void EditorHelper(const std::string_view label, ImColor* pointer, EditorHelperFlags flags)
    {
        ImGui::PushID(pointer);
        ImGui::ColorEdit4(label.data(), (float*)pointer);
        ImGui::PopID();
    }
}
