#pragma once
#include "../ImGuiEditor/ComponentWrapper.h"
#include "../ImGuiEditor/ImStructs.h"

// IMGUI_API bool          BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0);
// IMGUI_API void          EndCombo(); // only call EndCombo() if BeginCombo() returns true!
inline const ImStructs::ImGuiComponentFactory* Combo = new const ImStructs::ImGuiComponentFactory([]()
{
    const auto begin = ImStructs::make_component_wrapper(ImGui::BeginCombo, ImString("Hello, Combo!"), ImString("Hello, Combo!"), static_cast<ImGuiComboFlags>(0));
    begin->Name = "BeginCombo";
    begin->FunctionName = "ImGui::BeginCombo";
    begin->ArgumentNames = { "Text", "Preview Text", "Flags" };
    
    const auto end = ImStructs::make_component_wrapper(ImGui::EndCombo);
    end->Name = "EndCombo";
    end->FunctionName = "ImGui::EndCombo";
    end->ArgumentNames = { };
    
    const auto component = new ImStructs::ScopedImStruct(begin, end);
    component->Name = "Combo";
    return component;
});

//    IMGUI_API bool          BeginListBox(const char* label, const ImVec2& size = ImVec2(0, 0)); // open a framed scrolling region
//    IMGUI_API void          EndListBox();                                                       // only call EndListBox() if BeginListBox() returned true!
inline const ImStructs::ImGuiComponentFactory* ListBox = new const ImStructs::ImGuiComponentFactory([]()
{
    const auto begin = ImStructs::make_component_wrapper(ImGui::BeginListBox, ImString("Hello, List Box!"), static_cast<const ImVec2&>(ImVec2(0, 0)));
    begin->Name = "BeginListBox";
    begin->FunctionName = "ImGui::BeginListBox";
    begin->ArgumentNames = { "Text", "Size" };
    
    const auto end = ImStructs::make_component_wrapper(ImGui::EndListBox);
    end->Name = "EndListBox";
    end->FunctionName = "ImGui::EndListBox";
    end->ArgumentNames = { };
    
    const auto component = new ImStructs::ScopedImStruct(begin, end);
    component->Name = "ListBox";
    return component;
});

// IMGUI_API bool          BeginMenuBar();                                                     // append to menu-bar of current window (requires ImGuiWindowFlags_MenuBar flag set on parent window).
// IMGUI_API void          EndMenuBar();                                                       // only call EndMenuBar() if BeginMenuBar() returns true!
inline const ImStructs::ImGuiComponentFactory* MenuBar = new const ImStructs::ImGuiComponentFactory([]()
{
    const auto begin = ImStructs::make_component_wrapper(ImGui::BeginMenuBar);
    begin->Name = "BeginMenuBar";
    begin->FunctionName = "ImGui::BeginMenuBar";
    begin->ArgumentNames = { };
    
    const auto end = ImStructs::make_component_wrapper(ImGui::EndMenuBar);
    end->Name = "EndMenuBar";
    end->FunctionName = "ImGui::EndMenuBar";
    end->ArgumentNames = { };
    
    const auto component = new ImStructs::ScopedImStruct(begin, end);
    component->Name = "MenuBar";
    return component;
});

// IMGUI_API bool          BeginMenu(const char* label, bool enabled = true);                  // create a sub-menu entry. only call EndMenu() if this returns true!
// IMGUI_API void          EndMenu();                                                          // only call EndMenu() if BeginMenu() returns true!
inline const ImStructs::ImGuiComponentFactory* Menu = new const ImStructs::ImGuiComponentFactory([]()
{
    const auto begin = ImStructs::make_component_wrapper(ImGui::BeginMenu, ImString("Hello, Menu!"), static_cast<bool>(true));
    begin->Name = "BeginMenu";
    begin->FunctionName = "ImGui::BeginMenu";
    begin->ArgumentNames = { "Text", "Enabled" };
    
    const auto end = ImStructs::make_component_wrapper(ImGui::EndMenu);
    end->Name = "EndMenu";
    end->FunctionName = "ImGui::EndMenu";
    end->ArgumentNames = { };
    
    const auto component = new ImStructs::ScopedImStruct(begin, end);
    component->Name = "Menu";
    return component;
});

//    IMGUI_API bool          BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0);
//    IMGUI_API void          EndChild();
inline const ImStructs::ImGuiComponentFactory* Child = new const ImStructs::ImGuiComponentFactory([]()
{
    bool (*BeginChild)(const char*, const ImVec2&, bool, ImGuiWindowFlags) = ImGui::BeginChild;
    const auto begin = ImStructs::make_component_wrapper(BeginChild, ImString("Hello, Child!"), static_cast<const ImVec2&>(ImVec2(30, 30)), false, static_cast<int>(ImGuiWindowFlags_None));
    begin->Name = "BeginChild";
    begin->FunctionName = "ImGui::BeginChild";
    begin->ArgumentNames = { "Text", "Size", "Border", "Flags" };
    
    const auto end = ImStructs::make_component_wrapper(ImGui::EndChild);
    end->Name = "EndChild";
    end->FunctionName = "ImGui::EndChild";
    end->ArgumentNames = { };
    
    const auto component = new ImStructs::ScopedImStruct(begin, end);
    component->Name = "Child";
    return component;
});