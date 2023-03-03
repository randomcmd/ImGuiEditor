#include "ImGuiExtension.h"
#include <imgui_stdlib.h>

namespace ImGui
{
    bool TextEdit(const char* label, std::string* text, ImGuiInputTextFlags flags,
        ImGuiInputTextCallback callback, void* user_data)
    {
        return InputText(label, text, flags, callback, user_data);
    }

}
