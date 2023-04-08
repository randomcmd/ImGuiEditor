#include <fstream>
#include <iostream>
#include <map>

#include "ImStructs.h"
#include "ImGuiExtension.h"
#include "ImReflection.h"
#include "ImSerialise.h"

struct StyleReflection
{
    ImGuiStyle& Style;

    // ReSharper disable All
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
    // ReSharper restore All
};

std::map<ImGuiCol, std::string> CreateColorMap()
{
    std::map<ImGuiCol, std::string> map{};
    for(ImGuiCol i = 0; i < ImGuiCol_COUNT; i++)
    {
        map[i] = ImGui::GetStyleColorName(i);
    }
    return map;
}

static const std::map<ImGuiCol, std::string> ColorMap = CreateColorMap();

void ReMi::StyleEditor(ImGuiStyle& style)
{
    static std::string search = "";
    ImGui::InputText("Search", &search);
    if(ImGui::TreeNode("Colors"))
    {
        for(ImGuiCol i = 0; i < ImGuiCol_COUNT; i++)
        {
            const std::string_view color_name = ColorMap.at(i);
            if(!color_name.contains(search))
            {
                continue;
            }
            ImGui::PushID(i^0x12345678);
            ImGui::ColorEdit4("##color", &style.Colors[i].x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::Text("%s", color_name.data());
            ImGui::PopID();
        }
        ImGui::TreePop();
    }

    StyleReflection reflection(style);
    ImReflection::Editor(reflection.Members, search);
}

ImGuiStyle ReMi::RenewedStyle()
{
    ImGuiStyle pretty;
    ImVec4* colors = pretty.Colors;
    colors[ImGuiCol_Border]                 = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.48f, 0.48f, 0.48f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.98f, 0.98f, 0.98f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.98f, 0.98f, 0.98f, 0.67f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.98f, 0.98f, 0.98f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.98f, 0.98f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.98f, 0.98f, 0.98f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.75f, 0.75f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.98f, 0.98f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.98f, 0.98f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.98f, 0.98f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.58f, 0.58f, 0.58f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.98f, 0.98f, 0.98f, 0.80f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.68f, 0.68f, 0.68f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.15f, 0.15f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.98f, 0.98f, 0.98f, 0.70f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.98f, 0.98f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
    return pretty;
}

ImGuiStyle ReMi::VisualStudioRounded()
{
	// Rounded Visual Studio style by RedNicStone from ImThemes
	ImGuiStyle style;
	
	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.WindowRounding = 4.0f;
	style.WindowBorderSize = 0.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 0.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 4.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 2.5f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 11.0f;
	style.ScrollbarRounding = 2.5f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 2.0f;
	style.TabRounding = 3.5f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Right;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
	
	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5921568870544434f, 0.5921568870544434f, 0.5921568870544434f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.3529411852359772f, 0.3529411852359772f, 0.3725490272045135f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.3058823645114899f, 0.3058823645114899f, 0.3058823645114899f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2000000029802322f, 0.2000000029802322f, 0.2156862765550613f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.321568638086319f, 0.321568638086319f, 0.3333333432674408f, 1.0f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.1137254908680916f, 0.5921568870544434f, 0.9254902005195618f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.4666666686534882f, 0.7843137383460999f, 1.0f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);

	return style;
}

ImGuiStyle ReMi::ImportFromFile(std::filesystem::path path)
{
    ImGuiStyle style;

    // open file from path
    std::ifstream file(path);
    
    if(!file.is_open())
    {
        ImGui::StyleColorsDark(&style);
        std::cout << "Failed to open file: " << path << std::endl;
        return style;
    }

    std::string call_line;
    std::getline(file, call_line);
    while (!call_line.empty())
    {
        ImSerialisation::Call call(call_line);
        if(call.FunctionName == "StyleVar")
        {
            assert(call.Params.size() == 3 && "Incorrect amount of params for StyleVar");
            const auto style_var = call.Params[0];
            const auto type = ImReflection::GetType(call.Params[1]);
            // TODO: finish this code because I am too stupid for this
        }
        std::getline(file, call_line);
    }
    
    return style;
}
