#pragma once
#include "../ImGuiEditor/ComponentWrapper.h"
#include "../ImGuiEditor/ImStructs.h"

// IMGUI_API bool          TreeNode(const char* label);
// IMGUI_API void          TreePop();                                                          // ~ Unindent()+PopId()
inline const ImStructs::ImGuiComponentFactory* TreeNode = new const ImStructs::ImGuiComponentFactory([]()
{
    bool (*TreeNode)(const char*) = ImGui::TreeNode;
    const auto begin = ImStructs::make_component_wrapper(std::function(TreeNode), ImString("Hello, Tree Node!"));
    begin->Name = "TreeNode";
    begin->FunctionName = "ImGui::TreeNode";
    begin->ArgumentNames = { "Label" };
    
    const auto end = ImStructs::make_component_wrapper(ImGui::TreePop);
    end->Name = "TreePop";
    end->FunctionName = "ImGui::TreePop";
    end->ArgumentNames = { };
    
    const auto component = new ImStructs::ScopedImStruct(begin, end);
    component->Name = "TreeNode";
    return component;
});

// IMGUI_API bool          TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
// IMGUI_API float         GetTreeNodeToLabelSpacing();                                        // horizontal distance preceding label when using TreeNode*() or Bullet() == (g.FontSize + style.FramePadding.x*2) for a regular unframed TreeNode
inline const ImStructs::ImGuiComponentFactory* TreeNodeEx = new const ImStructs::ImGuiComponentFactory([]()
{
    bool (*TreeNodeEx)(const char*, ImGuiTreeNodeFlags) = ImGui::TreeNodeEx;
    const auto begin = ImStructs::make_component_wrapper(std::function(TreeNodeEx),
                                                         ImString("Hello, Tree Node!"),
                                                         static_cast<int>(ImGuiTreeNodeFlags_None));
    begin->Name = "TreeNodeEx";
    begin->FunctionName = "ImGui::TreeNodeEx";
    begin->ArgumentNames = { "Label", "Flags" };
    
    const auto end = ImStructs::make_component_wrapper(ImGui::TreePop);
    end->Name = "TreePop";
    end->FunctionName = "ImGui::TreePop";
    end->ArgumentNames = { };
    
    const auto component = new ImStructs::ScopedImStruct(begin, end);
    component->Name = "TreeNodeEx";
    return component;
});

// IMGUI_API bool          CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);  // if returning 'true' the header is open. doesn't indent nor push on ID stack. user doesn't have to call TreePop().
// [](){}
inline const ImStructs::ImGuiComponentFactory* CollapsingHeader = new const ImStructs::ImGuiComponentFactory([]()
{
    bool (*CollapsingHeader)(const char*, ImGuiTreeNodeFlags) = ImGui::CollapsingHeader;
    const auto begin = ImStructs::make_component_wrapper(std::function(CollapsingHeader),
                                                         ImString("Hello, Collapsing Header!"),
                                                         static_cast<int>(0));
    begin->Name = "CollapsingHeader";
    begin->FunctionName = "ImGui::CollapsingHeader";
    begin->ArgumentNames = { "Label", "Flags" };
    
    const auto end = ImStructs::make_component_wrapper([](){});
    end->Name = "No End Function";
    end->FunctionName = "";
    end->ArgumentNames = { };
    
    const auto component = new ImStructs::ScopedImStruct(begin, end);
    component->Name = "CollapsingHeader";
    return component;
});