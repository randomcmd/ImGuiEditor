#pragma once
#include <string>
#include "ImStructs.h"

namespace ImGui
{
    bool TextEdit(const char* label, std::string* text, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr); // TODO: Implement this quickly
    bool ColoredButtonV1(const char* label, const ImVec2& size, ImU32 text_color, ImU32 bg_color_1, ImU32 bg_color_2);
}
namespace ReMi
{
    void StyleEditor(ImGuiStyle& style);
    ImGuiStyle RenewedTheme();
    ImGuiStyle VisualStudioRounded();
    ImGuiStyle ImportFromFile(std::filesystem::path path);
}
