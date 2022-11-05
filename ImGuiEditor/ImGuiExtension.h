#pragma once
#include <string>

#include "ImGuiStructs.h"

namespace ImGui
{
    bool TextEdit(const char* label, std::string* text, bool* editing, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
}
