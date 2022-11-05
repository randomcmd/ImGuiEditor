#include "ImGuiExtension.h"

namespace ImGui
{
    bool TextEdit(const char* label, std::string* text, bool* editing, ImGuiInputTextFlags flags,
        ImGuiInputTextCallback callback, void* user_data)
    {
        auto valEditing = *editing;

        if(valEditing)
        {
            return InputText(label, text, flags, callback, user_data);
        }
        else
        {
            Text("%s", text->c_str());
        }

        if(IsItemClicked())
        {
            *editing = true;
        }
        else if(IsMouseClicked(ImGuiMouseButton_Left))
        {
            *editing = false;
        }

        return false;
    }
}
