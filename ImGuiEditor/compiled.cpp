#include <imgui.h>

#include "ImGuiExtension.h"

void Gui()
{
    static ImGuiStyle style = ImGui::GetStyle();
    ReMi::StyleEditor(style);
    if(ImGui::Button("Apply Style"))
    {
        ImGui::GetStyle() = style;
    }
}
