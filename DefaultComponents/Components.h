#pragma once
#include "../ImGuiEditor/ComponentWrapper.h"
#include "../ImGuiEditor/ImStructs.h"
#include "../ImGuiEditor/ImGuiExtension.h"
#include "../ImGuiEditor/ImString.h"

inline ImStructs::ImGuiComponentFactory* Text = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::TextUnformatted, ImString("Hello, World!"), nullptr);
    component->Name = "Text";
    component->FunctionName = "ImGui::TextUnformatted";
    component->ArgumentNames = {"Text", "End"};
    return component;
});

inline ImStructs::ImGuiComponentFactory* TextSeparator = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SeparatorText, ImString("Hello, World!"));
    component->Name = "SeparatorText";
    component->FunctionName = "ImGui::SeparatorText";
    component->ArgumentNames = {"Text"};
    return component;
});

inline ImStructs::ImGuiComponentFactory* Button = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::Button, ImString("Hello, Button!"), ImVec2(0, 0));
    component->Name = "Button";
    component->FunctionName = "ImGui::Button";
    component->ArgumentNames = {"Label", "Size"};
    return component;
});

//bool ImGui::ColoredButtonV1(const char* label, const ImVec2& size_arg, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2)
inline ImStructs::ImGuiComponentFactory* ColoredButtonV1 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ColoredButtonV1, ImString("Hello, Fancy Button!"), ImVec2(0, 0), *new ImColor(1.0f, 1.0f, 1.0f, 1.0f), *new ImColor(0xA020F0FF), *new ImColor(0x296d98FF));
    component->Name = "ColoredButtonV1";
    component->FunctionName = "ImGui::ColoredButtonV1";
    component->ArgumentNames = {"Label", "Size", "Text Color", "Top Color", "Bottom Color"};
    return component;
});

// SmallButton(const char*)
inline ImStructs::ImGuiComponentFactory* SmallButton = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SmallButton, ImString("Hello, Button!"));
    component->Name = "SmallButton";
    component->FunctionName = "ImGui::SmallButton";
    component->ArgumentNames = {"Label"};
    return component;
});

//     IMGUI_API bool          InvisibleButton(const char* str_id, const ImVec2& size, ImGuiButtonFlags flags = 0);
inline ImStructs::ImGuiComponentFactory* InvisibleButton = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::InvisibleButton, ImString("Hello, Button!"), ImVec2(0, 0), 
    static_cast<int>(ImGuiButtonFlags_None));
    component->Name = "InvisibleButton";
    component->FunctionName = "ImGui::InvisibleButton";
    component->ArgumentNames = {"Label", "Size", "Button Flags"};
    return component;
});

//     IMGUI_API bool          ArrowButton(const char* str_id, ImGuiDir dir);
inline ImStructs::ImGuiComponentFactory* ArrowButton = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ArrowButton, ImString("Hello, Button!"), static_cast<int>(ImGuiDir_Up));
    component->Name = "ArrowButton";
    component->FunctionName = "ImGui::ArrowButton";
    component->ArgumentNames = {"Label", "Direction"};
    return component;
});

//     IMGUI_API bool          Checkbox(const char* label, bool* v);
inline ImStructs::ImGuiComponentFactory* Checkbox = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::Checkbox, ImString("Hello, Checkbox!"), new bool(false));
    component->Name = "Checkbox";
    component->FunctionName = "ImGui::Checkbox";
    component->ArgumentNames = {"Label", "Value"};
    return component;
});

//    IMGUI_API bool          CheckboxFlags(const char* label, int* flags, int flags_value);
inline ImStructs::ImGuiComponentFactory* CheckboxFlags = new ImStructs::ImGuiComponentFactory([](){
    bool (*CheckboxFlags)(const char* label, int* flags, int flags_value) = ImGui::CheckboxFlags;
    const auto component = ImStructs::make_component_wrapper(std::function(CheckboxFlags), ImString("Hello, Checkbox!"), new int(0), 0);
    component->Name = "CheckboxFlags";
    component->FunctionName = "ImGui::CheckboxFlags";
    component->ArgumentNames = {"Label", "Flags", "Flags Value"};
    return component;
});

//    IMGUI_API bool          CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
inline ImStructs::ImGuiComponentFactory* CheckboxFlagsUnsigned = new ImStructs::ImGuiComponentFactory([](){
    bool (*CheckboxFlags)(const char* label, unsigned int* flags, unsigned int flags_value) = ImGui::CheckboxFlags;
    const auto component = ImStructs::make_component_wrapper(std::function(CheckboxFlags), ImString("Hello, Checkbox!"), new unsigned int(0), 0);
    component->Name = "CheckboxFlags";
    component->FunctionName = "ImGui::CheckboxFlags";
    component->ArgumentNames = {"Label", "Flags", "Flags Value"};
    return component;
});

//     IMGUI_API bool          RadioButton(const char* label, bool active);
inline ImStructs::ImGuiComponentFactory* RadioButton = new ImStructs::ImGuiComponentFactory([](){
    bool (*RadioButton)(const char* label, bool active) = ImGui::RadioButton;
    const auto component = ImStructs::make_component_wrapper(std::function(RadioButton), ImString("Hello, RadioButton!"), new bool(false));
    component->Name = "RadioButton";
    component->FunctionName = "ImGui::RadioButton";
    component->ArgumentNames = {"Label", "Active"};
    return component;
});

//    IMGUI_API bool          RadioButton(const char* label, int* v, int v_button);
inline ImStructs::ImGuiComponentFactory* RadioButtonInt = new ImStructs::ImGuiComponentFactory([](){
    bool (*RadioButton)(const char* label, int* v, int v_button) = ImGui::RadioButton;
    const auto component = ImStructs::make_component_wrapper(std::function(RadioButton), ImString("Hello, RadioButton!"), new int(0), 0);
    component->Name = "RadioButton";
    component->FunctionName = "ImGui::RadioButton";
    component->ArgumentNames = {"Label", "Value", "Value Button"};
    return component;
});

//    IMGUI_API void          ProgressBar(float fraction, const ImVec2& size_arg = ImVec2(-FLT_MIN, 0), const char* overlay = NULL);
inline ImStructs::ImGuiComponentFactory* ProgressBar = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::ProgressBar, 0.5f, ImVec2(-FLT_MIN, 0), ImString("Hello, ProgressBar!"));
    component->Name = "ProgressBar";
    component->FunctionName = "ImGui::ProgressBar";
    component->ArgumentNames = {"Fraction", "Size", "Overlay"};
    return component;
});

//    IMGUI_API void          Bullet();
inline ImStructs::ImGuiComponentFactory* Bullet = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::Bullet);
    component->Name = "Bullet";
    component->FunctionName = "ImGui::Bullet";
    component->ArgumentNames = {};
    return component;
});

// IMGUI_API void          Value(const char* prefix, bool b);
inline ImStructs::ImGuiComponentFactory* ValueBool = new ImStructs::ImGuiComponentFactory([](){
    void (*Value)(const char*, bool) = ImGui::Value;
    const auto component = ImStructs::make_component_wrapper(std::function(Value), ImString("Hello, Value!"), true);
    component->Name = "Value";
    component->FunctionName = "ImGui::Value";
    component->ArgumentNames = {"Prefix", "Value"};
    return component;
});


// IMGUI_API void          Value(const char* prefix, int v);
inline ImStructs::ImGuiComponentFactory* ValueInt = new ImStructs::ImGuiComponentFactory([](){
    void (*Value)(const char*, int) = ImGui::Value;
    const auto component = ImStructs::make_component_wrapper(std::function(Value), ImString("Hello, Value!"), 0);
    component->Name = "Value";
    component->FunctionName = "ImGui::Value";
    component->ArgumentNames = {"Prefix", "Value"};
    return component;
});

// IMGUI_API void          Value(const char* prefix, unsigned int v);
inline ImStructs::ImGuiComponentFactory* ValueUnsignedInt = new ImStructs::ImGuiComponentFactory([](){
    void (*Value)(const char* prefix, unsigned int v) = ImGui::Value;
    const auto component = ImStructs::make_component_wrapper(std::function(Value), ImString("Hello, Value!"), 0U);
    component->Name = "Value";
    component->FunctionName = "ImGui::Value";
    component->ArgumentNames = {"Prefix", "Value"};
    return component;
});

// IMGUI_API void          Value(const char* prefix, float v, const char* float_format = NULL);
inline ImStructs::ImGuiComponentFactory* ValueFloat = new ImStructs::ImGuiComponentFactory([](){
    void (*Value)(const char*, float, const char*) = ImGui::Value;
    const auto component = ImStructs::make_component_wrapper(std::function(Value), ImString("Hello, Value!"), 0.0f, ImString("%.3f"));
    component->Name = "Value";
    component->FunctionName = "ImGui::Value";
    component->ArgumentNames = {"Prefix", "Value", "Format"};
    return component;
});


// SKIP IMAGES FOR NOW BECAUSE HONESTLY I HAVE NO FUCKING IDEA HOW TO DO IMAGES RN
