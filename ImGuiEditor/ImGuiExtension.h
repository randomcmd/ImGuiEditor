#pragma once
#include <string>

#include "ImGuiStructs.h"
#include <imgui_internal.h>

namespace ImGui
{
    bool TextEdit(const char* label, std::string* text, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
}
