#pragma once
#include "../ImGuiEditor/ComponentWrapper.h"
#include "../ImGuiEditor/ImStructs.h"

//    IMGUI_API bool          InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
// inline const ImStructs::ImGuiComponentFactory* InputText = new ImStructs::ImGuiComponentFactory([](){
//     bool (*InputText)(const char*, char*, size_t, ImGuiInputTextFlags, ImGuiInputTextCallback, void*) = ImGui::InputText;
//     const auto component = ImStructs::make_component_wrapper(std::function(InputText), ImString("Hello, InputText!"), new char[256], 256, static_cast<int>(ImGuiInputTextFlags_None), nullptr, nullptr);
//     component->Name = "InputText";
//     component->FunctionName = "ImGui::InputText";
//     component->ArgumentNames = {"Label", "Buffer", "Buffer Size", "Input Text Flags", "Callback", "User Data"};
//     return component;
// });

// IMGUI_API bool          InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
// inline const ImStructs::ImGuiComponentFactory* InputTextMultiline = new ImStructs::ImGuiComponentFactory([](){
//     bool (*InputTextMultiline)(const char*, char*, size_t, const ImVec2&, ImGuiInputTextFlags, ImGuiInputTextCallback, void*) = ImGui::InputTextMultiline;
//     const auto component = ImStructs::make_component_wrapper(std::function(InputTextMultiline), ImString("Hello, InputTextMultiline!"), new char[256], 256, *new ImVec2(0, 0), static_cast<int>(ImGuiInputTextFlags_None), nullptr, nullptr);
//     component->Name = "InputTextMultiline";
//     component->FunctionName = "ImGui::InputTextMultiline";
//     component->ArgumentNames = {"Label", "Buffer", "Buffer Size", "Size", "Input Text Flags", "Callback", "User Data"};
//     return component;
// });

// IMGUI_API bool          InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
// inline const ImStructs::ImGuiComponentFactory* InputTextWithHint = new ImStructs::ImGuiComponentFactory([](){
//     bool (*InputTextWithHint)(const char*, const char*, char*, size_t, ImGuiInputTextFlags, ImGuiInputTextCallback, void*) = ImGui::InputTextWithHint;
//     const auto component = ImStructs::make_component_wrapper(std::function(InputTextWithHint), ImString("Hello, InputTextWithHint!"), ImString("Hint"), new char[256], 256, static_cast<int>(ImGuiInputTextFlags_None), nullptr, nullptr);
//     component->Name = "InputTextWithHint";
//     component->FunctionName = "ImGui::InputTextWithHint";
//     component->ArgumentNames = {"Label", "Hint", "Buffer", "Buffer Size", "Input Text Flags", "Callback", "User Data"};
//     return component;
// });

// IMGUI_API bool          InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputFloat = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputFloat)(const char*, float*, float, float, const char*, ImGuiInputTextFlags) = ImGui::InputFloat;
    const auto component = ImStructs::make_component_wrapper(std::function(InputFloat), ImString("Hello, InputFloat!"), new float(0.0f), 0.0f, 0.0f, ImString("%.3f"), static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputFloat";
    component->FunctionName = "ImGui::InputFloat";
    component->ArgumentNames = {"Label", "Value", "Step", "Step Fast", "Format", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputFloat2 = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputFloat2)(const char*, float*, const char*, ImGuiInputTextFlags) = ImGui::InputFloat2;
    const auto component = ImStructs::make_component_wrapper(std::function(InputFloat2), ImString("Hello, InputFloat2!"), new float[2]{0.0f, 0.0f}, ImString("%.3f"), static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputFloat2";
    component->FunctionName = "ImGui::InputFloat2";
    component->ArgumentNames = {"Label", "Value", "Format", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputFloat3 = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputFloat3)(const char*, float*, const char*, ImGuiInputTextFlags) = ImGui::InputFloat3;
    const auto component = ImStructs::make_component_wrapper(std::function(InputFloat3), ImString("Hello, InputFloat3!"), new float[3]{0.0f, 0.0f, 0.0f}, ImString("%.3f"), static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputFloat3";
    component->FunctionName = "ImGui::InputFloat3";
    component->ArgumentNames = {"Label", "Value", "Format", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputFloat4 = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputFloat4)(const char*, float*, const char*, ImGuiInputTextFlags) = ImGui::InputFloat4;
    const auto component = ImStructs::make_component_wrapper(std::function(InputFloat4), ImString("Hello, InputFloat4!"), new float[4]{0.0f, 0.0f, 0.0f, 0.0f}, ImString("%.3f"), static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputFloat4";
    component->FunctionName = "ImGui::InputFloat4";
    component->ArgumentNames = {"Label", "Value", "Format", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputInt = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputInt)(const char*, int*, int, int, ImGuiInputTextFlags) = ImGui::InputInt;
    const auto component = ImStructs::make_component_wrapper(std::function(InputInt), ImString("Hello, InputInt!"), new int(0), 1, 100, static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputInt";
    component->FunctionName = "ImGui::InputInt";
    component->ArgumentNames = {"Label", "Value", "Step", "Step Fast", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputInt2 = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputInt2)(const char*, int*, ImGuiInputTextFlags) = ImGui::InputInt2;
    const auto component = ImStructs::make_component_wrapper(std::function(InputInt2), ImString("Hello, InputInt2!"), new int[2]{0, 0}, static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputInt2";
    component->FunctionName = "ImGui::InputInt2";
    component->ArgumentNames = {"Label", "Value", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputInt3 = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputInt3)(const char*, int*, ImGuiInputTextFlags) = ImGui::InputInt3;
    const auto component = ImStructs::make_component_wrapper(std::function(InputInt3), ImString("Hello, InputInt3!"), new int[3]{0, 0, 0}, static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputInt3";
    component->FunctionName = "ImGui::InputInt3";
    component->ArgumentNames = {"Label", "Value", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputInt4 = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputInt4)(const char*, int*, ImGuiInputTextFlags) = ImGui::InputInt4;
    const auto component = ImStructs::make_component_wrapper(std::function(InputInt4), ImString("Hello, InputInt4!"), new int[4]{0, 0, 0, 0}, static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputInt4";
    component->FunctionName = "ImGui::InputInt4";
    component->ArgumentNames = {"Label", "Value", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* InputDouble = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputDouble)(const char*, double*, double, double, const char*, ImGuiInputTextFlags) = ImGui::InputDouble;
    const auto component = ImStructs::make_component_wrapper(std::function(InputDouble), ImString("Hello, InputDouble!"), new double(0.0), 0.0, 0.0, ImString("%.6f"), static_cast<int>(ImGuiInputTextFlags_None));
    component->Name = "InputDouble";
    component->FunctionName = "ImGui::InputDouble";
    component->ArgumentNames = {"Label", "Value", "Step", "Step Fast", "Format", "Input Text Flags"};
    return component;
});

// IMGUI_API bool          InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
// inline const ImStructs::ImGuiComponentFactory* InputScalar = new ImStructs::ImGuiComponentFactory([](){
//     bool (*InputScalar)(const char*, ImGuiDataType, void*, const void*, const void*, const char*, ImGuiInputTextFlags) = ImGui::InputScalar;
//     const auto component = ImStructs::make_component_wrapper(std::function(InputScalar), ImString("Hello, InputScalar!"), static_cast<int>(ImGuiDataType_Float), new float(0.0f), 
//     static_cast<const void*>(nullptr), static_cast<const void*>(nullptr), ImString("%.3f"), static_cast<int>(ImGuiInputTextFlags_None));
//     component->Name = "InputScalar";
//     component->FunctionName = "ImGui::InputScalar";
//     component->ArgumentNames = {"Label", "Data Type", "Value", "Step", "Step Fast", "Format", "Input Text Flags"};
//     return component;
// });

// IMGUI_API bool          InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0);
// inline const ImStructs::ImGuiComponentFactory* InputScalarN = new ImStructs::ImGuiComponentFactory([](){
//     bool (*InputScalarN)(const char*, ImGuiDataType, void*, int, const void*, const void*, const char*, ImGuiInputTextFlags) = ImGui::InputScalarN;
//     const auto component = ImStructs::make_component_wrapper(std::function(InputScalarN), ImString("Hello, InputScalarN!"), static_cast<int>(ImGuiDataType_Float), new float[4]{0.0f, 0.0f, 0.0f, 0.0f}, 4, static_cast<const void*>(nullptr), static_cast<const void*>(nullptr), ImString("%.3f"), static_cast<int>(ImGuiInputTextFlags_None));
//     component->Name = "InputScalarN";
//     component->FunctionName = "ImGui::InputScalarN";
//     component->ArgumentNames = {"Label", "Data Type", "Value", "Components", "Step", "Step Fast", "Format", "Input Text Flags"};
//     return component;
// });

// IMGUI_API bool  InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
inline const ImStructs::ImGuiComponentFactory* InputTextStdString = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputText)(const char*, std::string*, ImGuiInputTextFlags, ImGuiInputTextCallback, void*) = ImGui::InputText;
    const auto component = ImStructs::make_component_wrapper(std::function(InputText), ImString("Hello, InputText!"), new std::string(), static_cast<int>(ImGuiInputTextFlags_None), static_cast<ImGuiInputTextCallback>(nullptr), static_cast<void*>(nullptr));
    component->Name = "InputTextStdString";
    component->FunctionName = "ImGui::InputText";
    component->ArgumentNames = {"Label", "Value", "Input Text Flags", "Callback", "User Data"};
    return component;
});

// IMGUI_API bool  InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
inline const ImStructs::ImGuiComponentFactory* InputTextMultilineStdString = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputTextMultiline)(const char*, std::string*, const ImVec2&, ImGuiInputTextFlags, ImGuiInputTextCallback, void*) = ImGui::InputTextMultiline;
    const auto component = ImStructs::make_component_wrapper(std::function(InputTextMultiline), ImString("Hello, InputTextMultiline!"), new std::string(), ImVec2(0, 0), static_cast<int>(ImGuiInputTextFlags_None), static_cast<ImGuiInputTextCallback>(nullptr), static_cast<void*>(nullptr));
    component->Name = "InputTextMultilineStdString";
    component->FunctionName = "ImGui::InputTextMultiline";
    component->ArgumentNames = {"Label", "Value", "Size", "Input Text Flags", "Callback", "User Data"};
    return component;
});

// IMGUI_API bool  InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
inline const ImStructs::ImGuiComponentFactory* InputTextWithHintStdString = new ImStructs::ImGuiComponentFactory([](){
    bool (*InputTextWithHint)(const char*, const char*, std::string*, ImGuiInputTextFlags, ImGuiInputTextCallback, void*) = ImGui::InputTextWithHint;
    const auto component = ImStructs::make_component_wrapper(std::function(InputTextWithHint), ImString("Hello, InputTextWithHint!"), ImString("Hello, Hint!"), new std::string(), static_cast<int>(ImGuiInputTextFlags_None), static_cast<ImGuiInputTextCallback>(nullptr), static_cast<void*>(nullptr));
    component->Name = "InputTextWithHintString";
    component->FunctionName = "ImGui::InputTextWithHint";
    component->ArgumentNames = {"Label", "Hint", "Value", "Input Text Flags", "Callback", "User Data"};
    return component;
});
