#include "ImGuiExtension.h"
#include "ImReflection.h"

struct StyleReflection
{
    ImGuiStyle Style;

    std::vector<ImReflection::Member> Members = {
        { ImReflection::CATEGORY, "Window Values" },
        { ImReflection::VEC2, "Window Padding", &Style.WindowPadding },
        { ImReflection::FLOAT, "Window Rounding", &Style.WindowRounding },
        { ImReflection::FLOAT, "Window Border Size", &Style.WindowBorderSize },
        { ImReflection::VEC2, "Window Min Size", &Style.WindowMinSize },
        { ImReflection::VEC2, "Window Title Align", &Style.WindowTitleAlign },
        { ImReflection::INT, "Window Menu Button Position", &Style.WindowMenuButtonPosition },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Child Values"},
        { ImReflection::FLOAT, "Child Rounding", &Style.ChildRounding },
        { ImReflection::FLOAT, "Child Border Size", &Style.ChildBorderSize },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Pop Up Values" },
        { ImReflection::FLOAT, "Pop Up Rounding", &Style.PopupRounding },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Frame Values"},
        { ImReflection::FLOAT, "Frame Padding", &Style.FramePadding },
        { ImReflection::FLOAT, "Frame Rounding", &Style.FrameRounding },
        { ImReflection::FLOAT, "Frame Border Size", &Style.FrameBorderSize },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Item Values"},
        { ImReflection::VEC2, "Item Spacing", &Style.ItemSpacing },
        { ImReflection::VEC2, "Item Inner Spacing", &Style.ItemInnerSpacing },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Cell Values"},
        { ImReflection::VEC2, "Cell Padding", &Style.CellPadding },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Touch Values"},
        { ImReflection::VEC2, "Touch Extra Padding", &Style.TouchExtraPadding },
        { ImReflection::CATEGORY_POP},

        { ImReflection::CATEGORY, "Indent Values"},
        { ImReflection::FLOAT, "Indent Spacing", &Style.IndentSpacing},
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Collumn Values"},
        { ImReflection::FLOAT, "Column Minimum Spacing", &Style.ColumnsMinSpacing},
        { ImReflection::CATEGORY_POP},

        { ImReflection::CATEGORY, "Scrollbar Values" },
        { ImReflection::FLOAT, "Scrollbar Size", &Style.ScrollbarSize },
        { ImReflection::FLOAT, "Scrollbar Rounding", &Style.ScrollbarRounding },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Slider Values" },
        { ImReflection::FLOAT, "Grab Minimum Size", &Style.GrabMinSize},
        { ImReflection::FLOAT, "Grab Rounding", &Style.GrabRounding},
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Logarithmic Slider Values" },
        { ImReflection::FLOAT, "Death Zone",  &Style.LogSliderDeadzone},
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Tab Values" },
        { ImReflection::FLOAT, "Tab Rounding", &Style.TabRounding },
        { ImReflection::FLOAT, "Tab Border Size", &Style.ChildBorderSize },
        { ImReflection::FLOAT, "Tab Minimum Width For Close Button", &Style.TabMinWidthForCloseButton },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Color Button Values" },
        { ImReflection::INT, "Color Button Position", &Style.ColorButtonPosition },
        { ImReflection::CATEGORY_POP },
            
        { ImReflection::CATEGORY, "Button Values" },
        { ImReflection::VEC2, "Button Text Align", &Style.ButtonTextAlign },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Selectable Values" },
        { ImReflection::VEC2, "Selectable Text Align", &Style.SelectableTextAlign },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Display Window Values" },
        { ImReflection::VEC2, "Display Window Padding", &Style.DisplayWindowPadding },
        { ImReflection::VEC2, "Display Safe Area Padding", &Style.DisplaySafeAreaPadding },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Mouse Cursor Values" },
        { ImReflection::FLOAT, "Mouse Cursor Scale", &Style.MouseCursorScale },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Anti Aliasing Values" },
        { ImReflection::BOOL, "Anti Aliased Lines", &Style.AntiAliasedLines },
        { ImReflection::BOOL, "Anti Aliased Line Use Text", &Style.AntiAliasedLinesUseTex },
        { ImReflection::BOOL, "Anti Aliased Fill", &Style.AntiAliasedFill },
        { ImReflection::CATEGORY_POP },

        { ImReflection::CATEGORY, "Curve Values"},
        { ImReflection::FLOAT, "Curve Tessellation Tolerance", &Style.CurveTessellationTol},
        { ImReflection::FLOAT, "Circle Tesselation Maximum Error", &Style.CircleTessellationMaxError},
        { ImReflection::CATEGORY_POP },
        
        { ImReflection::CATEGORY, "Global Alpha Values"},
        { ImReflection::FLOAT, "Global Alpha", &Style.Alpha },
        { ImReflection::FLOAT, "Disabled Alpha", &Style.Alpha },
        { ImReflection::CATEGORY_POP }
    };
};

void ReMi::StyleEditor(ImGuiStyle& style)
{
    if(ImGui::TreeNode("Colors"))
    {
        for(size_t i= 0; i < ImGuiCol_COUNT; i++)
        {
            ImGui::PushID(i^0x12345678);
            ImGui::ColorEdit4("##color", &style.Colors[i].x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::Text("%s", ImGui::GetStyleColorName(i));
            ImGui::PopID();
        }
        ImGui::TreePop();
    }

    StyleReflection reflection;
    reflection.Style = style;
    ImReflection::Editor(reflection.Members);
}
