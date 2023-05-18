#pragma once
#include "../ImGuiEditor/ComponentWrapper.h"
#include "../ImGuiEditor/ImStructs.h"

//    IMGUI_API bool          DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* DragFloat = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::DragFloat, ImString("Hello, DragFloat!"), new float(0.0f), 1.0f, 0.0f, 0.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "DragFloat";
    component->FunctionName = "ImGui::DragFloat";
    component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* DragFloat2 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::DragFloat2, ImString("Hello, DragFloat2!"), new float[2]{0.0f, 0.0f}, 1.0f, 0.0f, 0.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "DragFloat2";
    component->FunctionName = "ImGui::DragFloat2";
    component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* DragFloat3 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::DragFloat3, ImString("Hello, DragFloat3!"), new float[3]{0.0f, 0.0f, 0.0f}, 1.0f, 0.0f, 0.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "DragFloat3";
    component->FunctionName = "ImGui::DragFloat3";
    component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* DragFloat4 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::DragFloat4, ImString("Hello, DragFloat4!"), new float[4]{0.0f, 0.0f, 0.0f, 0.0f}, 1.0f, 0.0f, 0.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "DragFloat4";
    component->FunctionName = "ImGui::DragFloat4";
    component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, ImGuiSliderFlags flags = 0);
// inline const ImStructs::ImGuiComponentFactory* DragFloatRange2 = new ImStructs::ImGuiComponentFactory([](){
//     const auto component = ImStructs::make_component_wrapper(ImGui::DragFloatRange2, ImString("Hello, DragFloatRange2!"), new float[2]{0.0f, 0.0f}, 1.0f, 0.0f, 0.0f, ImString("%.3f"), ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
//     component->Name = "DragFloatRange2";
//     component->FunctionName = "ImGui::DragFloatRange2";
//     component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "FormatMax", "Flags"};
//     return component;
// });

// IMGUI_API bool          DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);  // If v_min >= v_max we have no bound
inline const ImStructs::ImGuiComponentFactory* DragInt = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::DragInt, ImString("Hello, DragInt!"), new int(0), 1.0f, 0, 0, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "DragInt";
    component->FunctionName = "ImGui::DragInt";
    component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* DragInt2 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::DragInt2, ImString("Hello, DragInt2!"), new int[2]{0, 0}, 1.0f, 0, 0, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "DragInt2";
    component->FunctionName = "ImGui::DragInt2";
    component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* DragInt3 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::DragInt3, ImString("Hello, DragInt3!"), new int[3]{0, 0, 0}, 1.0f, 0, 0, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "DragInt3";
    component->FunctionName = "ImGui::DragInt3";
    component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* DragInt4 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::DragInt4, ImString("Hello, DragInt4!"), new int[4]{0, 0, 0, 0}, 1.0f, 0, 0, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "DragInt4";
    component->FunctionName = "ImGui::DragInt4";
    component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = NULL, ImGuiSliderFlags flags = 0);
// inline const ImStructs::ImGuiComponentFactory* DragIntRange2 = new ImStructs::ImGuiComponentFactory([](){
//     const auto component = ImStructs::make_component_wrapper(ImGui::DragIntRange2, ImString("Hello, DragIntRange2!"), new int[2]{0, 0}, 1.0f, 0, 0, ImString("%d"), ImString(nullptr), static_cast<int>(ImGuiSliderFlags_None));
//     component->Name = "DragIntRange2";
//     component->FunctionName = "ImGui::DragIntRange2";
//     component->ArgumentNames = {"Label", "Value", "Speed", "Min", "Max", "Format", "FormatMax", "Flags"};
//     return component;
// });

// IMGUI_API bool          DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed = 1.0f, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0);
// inline const ImStructs::ImGuiComponentFactory* DragScalar = new ImStructs::ImGuiComponentFactory([](){
//     const auto component = ImStructs::make_component_wrapper(ImGui::DragScalar, ImString("Hello, DragScalar!"), ImGuiDataType_Float, new float(0.0f), 1.0f, 0.0f, 0.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
//     component->Name = "DragScalar";
//     component->FunctionName = "ImGui::DragScalar";
//     component->ArgumentNames = {"Label", "DataType", "Value", "Speed", "Min", "Max", "Format", "Flags"};
//     return component;
// });

// IMGUI_API bool          DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed = 1.0f, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0);
// inline const ImStructs::ImGuiComponentFactory* DragScalarN = new ImStructs::ImGuiComponentFactory([](){
//     const auto component = ImStructs::make_component_wrapper(ImGui::DragScalarN, ImString("Hello, DragScalarN!"), ImGuiDataType_Float, new float[2]{0.0f, 0.0f}, 2, 1.0f, 0.0f, 0.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
//     component->Name = "DragScalarN";
//     component->FunctionName = "ImGui::DragScalarN";
//     component->ArgumentNames = {"Label", "DataType", "Value", "Components", "Speed", "Min", "Max", "Format", "Flags"};
//     return component;
// });

// IMGUI_API bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);     // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display.
inline const ImStructs::ImGuiComponentFactory* SliderFloat = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderFloat, ImString("Hello, SliderFloat!"), new float(0.0f), 0.0f, 1.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderFloat";
    component->FunctionName = "ImGui::SliderFloat";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderFloat2 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderFloat2, ImString("Hello, SliderFloat2!"), new float[2]{0.0f, 0.0f}, 0.0f, 1.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderFloat2";
    component->FunctionName = "ImGui::SliderFloat2";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderFloat3 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderFloat3, ImString("Hello, SliderFloat3!"), new float[3]{0.0f, 0.0f, 0.0f}, 0.0f, 1.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderFloat3";
    component->FunctionName = "ImGui::SliderFloat3";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderFloat4 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderFloat4, ImString("Hello, SliderFloat4!"), new float[4]{0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 1.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderFloat4";
    component->FunctionName = "ImGui::SliderFloat4";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderAngle = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderAngle, ImString("Hello, SliderAngle!"), new float(0.0f), -360.0f, 360.0f, ImString("%.0f deg"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderAngle";
    component->FunctionName = "ImGui::SliderAngle";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderInt = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderInt, ImString("Hello, SliderInt!"), new int(0), 0, 100, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderInt";
    component->FunctionName = "ImGui::SliderInt";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderInt2 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderInt2, ImString("Hello, SliderInt2!"), new int[2]{0, 0}, 0, 100, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderInt2";
    component->FunctionName = "ImGui::SliderInt2";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderInt3 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderInt3, ImString("Hello, SliderInt3!"), new int[3]{0, 0, 0}, 0, 100, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderInt3";
    component->FunctionName = "ImGui::SliderInt3";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderInt4 = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderInt4, ImString("Hello, SliderInt4!"), new int[4]{0, 0, 0, 0}, 0, 100, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderInt4";
    component->FunctionName = "ImGui::SliderInt4";
    component->ArgumentNames = {"Label", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);

inline const ImStructs::ImGuiComponentFactory* SliderScalar = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderScalar, ImString("Hello, SliderScalar!"), static_cast<int>(ImGuiDataType_Float), new float(0.0f), new float(0.0f), new float(1.0f), ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderScalar";
    component->FunctionName = "ImGui::SliderScalar";
    component->ArgumentNames = {"Label", "Data Type", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});
// IMGUI_API bool          SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* SliderScalarN = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::SliderScalarN, ImString("Hello, SliderScalarN!"), static_cast<int>(ImGuiDataType_Float), new float[4]{0.0f, 0.0f, 0.0f, 0.0f}, 4, new float(0.0f), new float(1.0f), ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "SliderScalarN";
    component->FunctionName = "ImGui::SliderScalarN";
    component->ArgumentNames = {"Label", "Data Type", "Value", "Components", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* VSliderFloat = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::VSliderFloat, ImString("Hello, VSliderFloat!"), *new ImVec2(20.0f, 100.0f), new float(0.0f), 0.0f, 1.0f, ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "VSliderFloat";
    component->FunctionName = "ImGui::VSliderFloat";
    component->ArgumentNames = {"Label", "Size", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
inline const ImStructs::ImGuiComponentFactory* VSliderInt = new ImStructs::ImGuiComponentFactory([](){
    const auto component = ImStructs::make_component_wrapper(ImGui::VSliderInt, ImString("Hello, VSliderInt!"), *new ImVec2(20.0f, 100.0f), new int(0), 0, 100, ImString("%d"), static_cast<int>(ImGuiSliderFlags_None));
    component->Name = "VSliderInt";
    component->FunctionName = "ImGui::VSliderInt";
    component->ArgumentNames = {"Label", "Size", "Value", "Min", "Max", "Format", "Flags"};
    return component;
});

// IMGUI_API bool          VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0);
// inline const ImStructs::ImGuiComponentFactory* VSliderScalar = new ImStructs::ImGuiComponentFactory([](){
//     const auto component = ImStructs::make_component_wrapper(ImGui::VSliderScalar, ImString("Hello, VSliderScalar!"), new ImVec2(20.0f, 100.0f), static_cast<int>(ImGuiDataType_Float), new float(0.0f), new float(0.0f), new float(1.0f), ImString("%.3f"), static_cast<int>(ImGuiSliderFlags_None));
//     component->Name = "VSliderScalar";
//     component->FunctionName = "ImGui::VSliderScalar";
//     component->ArgumentNames = {"Label", "Size", "Data Type", "Value", "Min", "Max", "Format", "Flags"};
//     return component;
// });
