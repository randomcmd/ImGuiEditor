#include "DefaultThemes.h"

#include <string>

ImGuiStyle ReMi::RenewedTheme()
{
    ImGuiStyle pretty;

	// Shades of rem
	const ImColor rem = ImColor(176, 214, 251);
	const ImColor rem_outline = ImColor(67, 131, 191);
	const ImColor rem_hairclip = ImColor(186, 125, 211);

	const ImColor backround = ImColor(37, 37, 37);
	const ImColor lighter = ImColor(64, 64, 64);

	// Shades of white
	const ImColor w0 = ImColor(128, 128, 128);
	const ImColor w1 = ImColor(164, 164, 164);
	const ImColor w2 = ImColor(222, 222, 222);
	const ImColor w3 = ImColor(244, 244, 244);

	const ImColor highlight = ImColor(45, 88 ,128);
	const ImColor highlight_lighter = ImColor(67, 131, 191);
	const ImColor highlight_hovered = ImColor(77, 152, 222);
	const ImColor highlight_active = ImColor(89, 175, 255);
	
	
    ImVec4* colors = pretty.Colors;

	pretty.Alpha = 1.0f;
	pretty.DisabledAlpha = 0.6000000238418579f;
	pretty.WindowPadding = ImVec2(8.0f, 8.0f);
	pretty.WindowRounding = 4.0f;
	pretty.WindowBorderSize = 1.0f;
	pretty.WindowMinSize = ImVec2(32.0f, 32.0f);
	pretty.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	pretty.WindowMenuButtonPosition = ImGuiDir_Left;
	pretty.ChildRounding = 0.0f;
	pretty.ChildBorderSize = 1.0f;
	pretty.PopupRounding = 0.0f;
	pretty.PopupBorderSize = 1.0f;
	pretty.FramePadding = ImVec2(4.0f, 3.0f);
	pretty.FrameRounding = 4.0f;
	pretty.FrameBorderSize = 0.0f;
	pretty.ItemSpacing = ImVec2(4.0f, 4.0f);
	pretty.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	pretty.CellPadding = ImVec2(4.0f, 2.0f);
	pretty.IndentSpacing = 20.0f;
	pretty.ColumnsMinSpacing = 6.0f;
	pretty.ScrollbarSize = 14.0f;
	pretty.ScrollbarRounding = 9.0f;
	pretty.GrabMinSize = 10.0f;
	pretty.GrabRounding = 4.0f;
	pretty.TabRounding = 4.0f;
	pretty.TabBorderSize = 0.0f;
	pretty.TabMinWidthForCloseButton = 0.0f;
	pretty.ColorButtonPosition = ImGuiDir_Right;
	pretty.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	pretty.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	// Text
	colors[ImGuiCol_Text] =					ImColor(255, 255, 255);
	colors[ImGuiCol_TextDisabled] =			lighter;

	// Backrounds and Borders (Window, Child, Popup)
	colors[ImGuiCol_WindowBg] =				backround;
	colors[ImGuiCol_ChildBg] =				backround;
	colors[ImGuiCol_PopupBg] =				backround;
	colors[ImGuiCol_Border] =					lighter;
	colors[ImGuiCol_BorderShadow] =			lighter;

	// Frames
	colors[ImGuiCol_FrameBg] =				lighter;
	colors[ImGuiCol_FrameBgHovered] =			w0;
	colors[ImGuiCol_FrameBgActive] =			w1;

	// Titles
	colors[ImGuiCol_TitleBg] =				backround;
	colors[ImGuiCol_TitleBgActive] =			lighter;
	colors[ImGuiCol_TitleBgCollapsed] =		backround;
	colors[ImGuiCol_MenuBarBg] =				backround;

	// Scrollbar
	colors[ImGuiCol_ScrollbarBg] =			lighter;
	colors[ImGuiCol_ScrollbarGrab] =			w1;
	colors[ImGuiCol_ScrollbarGrabHovered] =	w2;
	colors[ImGuiCol_ScrollbarGrabActive] =	w3;

	// Misc highlights
	colors[ImGuiCol_CheckMark] =				highlight_lighter;
	colors[ImGuiCol_SliderGrab] =				highlight_lighter;
	colors[ImGuiCol_SliderGrabActive] =		highlight_active;

	// Buttons my beloved <3
	colors[ImGuiCol_Button] =					highlight;
	colors[ImGuiCol_ButtonHovered] =			highlight_hovered;
	colors[ImGuiCol_ButtonActive] =			highlight_active;

	// Headers
	colors[ImGuiCol_Header] =					lighter;
	colors[ImGuiCol_HeaderHovered] =			w1;
	colors[ImGuiCol_HeaderActive] =			w2;

	// Separators
	colors[ImGuiCol_Separator] =				lighter;
	colors[ImGuiCol_SeparatorHovered] =		w0;
	colors[ImGuiCol_SeparatorActive] =		w1;

	// Resizing
	colors[ImGuiCol_ResizeGrip] =				highlight_lighter;
	colors[ImGuiCol_ResizeGripHovered] =		highlight_hovered;
	colors[ImGuiCol_ResizeGripActive] =		highlight_active;

	// Tabs Tabs Tabs
	colors[ImGuiCol_Tab] =					lighter;
	colors[ImGuiCol_TabHovered]	=				highlight_hovered;
	colors[ImGuiCol_TabActive] =				highlight;
	colors[ImGuiCol_TabUnfocused] =			lighter;
	colors[ImGuiCol_TabUnfocusedActive] =		highlight;

	// Plots
	colors[ImGuiCol_PlotLines] =				highlight_lighter;
	colors[ImGuiCol_PlotLinesHovered] =		highlight_hovered;
	colors[ImGuiCol_PlotHistogram] =			highlight_lighter;
	colors[ImGuiCol_PlotHistogramHovered] =	highlight_hovered;

	// Tables
	colors[ImGuiCol_TableHeaderBg] =			backround;
	colors[ImGuiCol_TableBorderStrong] =		w1;
	colors[ImGuiCol_TableBorderLight] =		w0;
	colors[ImGuiCol_TableRowBg] =				backround;
	colors[ImGuiCol_TableRowBgAlt] =			backround;
	colors[ImGuiCol_TextSelectedBg] =			w1;

	// Drag and drop
	colors[ImGuiCol_DragDropTarget] =			rem_hairclip;

	// Nav and modal
	colors[ImGuiCol_NavHighlight] =			highlight_lighter;
	colors[ImGuiCol_NavWindowingHighlight] =	w1;
	colors[ImGuiCol_ModalWindowDimBg] =		ImColor(255, 255, 255, 64);
	colors[ImGuiCol_ModalWindowDimBg] =		ImColor(255, 255, 255, 64);
	
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
	//style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.1450980454683304f, 0.1450980454683304f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.25f);

	return style;
}

