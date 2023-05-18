#pragma once
#include "../ImGuiEditor/ComponentWrapper.h"
#include "../ImGuiEditor/ImStructs.h"

//    IMGUI_API bool          ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* ColorEdit3 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ColorEdit3, ImString("Hello, ColorEdit3!"), new float[3]{0.0f, 0.0f, 0.0f}, static_cast<int>(ImGuiColorEditFlags_None));
    component->Name = "ColorEdit3";
    component->FunctionName = "ImGui::ColorEdit3";
    component->ArgumentNames = {"Label", "Color", "Color Edit Flags"};
    return component;
});

// IMGUI_API bool          ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* ColorEdit4 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ColorEdit4, ImString("Hello, ColorEdit4!"), new float[4]{0.0f, 0.0f, 0.0f, 0.0f}, static_cast<int>(ImGuiColorEditFlags_None));
    component->Name = "ColorEdit4";
    component->FunctionName = "ImGui::ColorEdit4";
    component->ArgumentNames = {"Label", "Color", "Color Edit Flags"};
    return component;
});

// IMGUI_API bool          ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* ColorPicker3 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ColorPicker3, ImString("Hello, ColorPicker3!"), new float[3]{0.0f, 0.0f, 0.0f}, static_cast<int>(ImGuiColorEditFlags_None));
    component->Name = "ColorPicker3";
    component->FunctionName = "ImGui::ColorPicker3";
    component->ArgumentNames = {"Label", "Color", "Color Edit Flags"};
    return component;
});

// IMGUI_API bool          ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
inline const ImStructs::ImGuiComponentFactory* ColorPicker4 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ColorPicker4, ImString("Hello, ColorPicker4!"), new float[4]{0.0f, 0.0f, 0.0f, 0.0f}, static_cast<int>(ImGuiColorEditFlags_None), new float[4]{0.0f, 0.0f, 0.0f, 0.0f});
    component->Name = "ColorPicker4";
    component->FunctionName = "ImGui::ColorPicker4";
    component->ArgumentNames = {"Label", "Color", "Color Edit Flags", "Reference Color"};
    return component;
});

// IMGUI_API bool          ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // display a color square/button, hover for details, return true when pressed.
inline const ImStructs::ImGuiComponentFactory* ColorButton = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ColorButton, ImString("Hello, ColorButton!"), ImVec4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<int>(ImGuiColorEditFlags_None), ImVec2(0.0f, 0.0f));
    component->Name = "ColorButton";
    component->FunctionName = "ImGui::ColorButton";
    component->ArgumentNames = {"Description ID", "Color", "Color Edit Flags", "Size"};
    return component;
});

// IMGUI_API bool          Selectable(const char* label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0)); // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
inline const ImStructs::ImGuiComponentFactory* Selectable = new ImStructs::ImGuiComponentFactory([](){
    bool (*Selectable)(const char* label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size) = ImGui::Selectable;
    const auto component = ImStructs::make_component_wrapper(Selectable, ImString("Hello, Selectable!"), false, static_cast<int>(ImGuiSelectableFlags_None), ImVec2(0.0f, 0.0f));
    component->Name = "Selectable";
    component->FunctionName = "ImGui::Selectable";
    component->ArgumentNames = {"Label", "Selected", "Selectable Flags", "Size"};
    return component;
});

// IMGUI_API bool          Selectable(const char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0, 0));      // "bool* p_selected" point to the selection state (read-write), as a convenient helper.
inline const ImStructs::ImGuiComponentFactory* SelectableWithPointer = new ImStructs::ImGuiComponentFactory([](){
    bool (*Selectable)(const char* label, bool* p_selected, ImGuiSelectableFlags flags, const ImVec2& size) = ImGui::Selectable;
    const auto component = ImStructs::make_component_wrapper(Selectable, ImString("Hello, Selectable!"), new bool(false), static_cast<int>(ImGuiSelectableFlags_None), ImVec2(0.0f, 0.0f));
    component->Name = "Selectable";
    component->FunctionName = "ImGui::Selectable";
    component->ArgumentNames = {"Label", "Selected", "Selectable Flags", "Size"};
    return component;
});
