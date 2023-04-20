#include <iostream>
#include <sstream>

#include "ImStructs.h"
#include "ImSerialise.h"

namespace ImStructs
{
    std::string ImStruct::Serialise() const
    {
        return "ImStruct(\"" + Label + "\")";
    }

    void ImStruct::Deserialise(std::string str)
    {
        const ImSerialisation::Call call(str);
        assert(call.Params.size() == 1 && "ImStruct::Deserialise incorrect number of arguments (only takes label)");
        auto ss = std::stringstream(call.Params[0]);
        ImDeserialise(ss, Label);
    }

    std::string ImStruct::Compile()
    {
        return "You're supposed to override this duh 🙄";
    }

    void ImStructComponent::PreDraw()
    {
        FallBackLabel = Label.c_str();
        CursorTemp = ImGui::GetCursorPos();
        if (ComponentFlags & ComponentFlags_OverridePosition)
        {
            ImGui::SetCursorPos(Position);
        }
        if (Width != 0.0f)
        {
            ImGui::SetNextItemWidth(Width);
        }
        if (ComponentFlags & ComponentFlags_SameLine)
        {
            ImGui::SameLine();
        }
    }

    void ImStructComponent::Cleanup()
    {
        if (ComponentFlags & ComponentFlags_OverridePosition)
        {
            ImGui::SetCursorPos(CursorTemp);
        }
    }

    void ImStructComponent::Draw()
    {
    }

    void ImStructComponent::PostDraw()
    {
        if(!CustomClickBehaviour) {
            if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
            if(ImGui::IsItemClicked()) CanvasFlags |= ImStructs::CanvasFlags_Clicked;
        }
        if (ComponentFlags & ComponentFlags_OverridePosition)
        {
            constexpr auto padding = 3.0f;
            const ImVec2 inner_rect_min = {ImGui::GetItemRectMin().x + padding, ImGui::GetItemRectMin().y + padding};
            const ImVec2 inner_rect_max = {ImGui::GetItemRectMax().x - padding, ImGui::GetItemRectMax().y - padding};
            if (!ImGui::IsMouseHoveringRect(inner_rect_min, inner_rect_max))
            {
                ImGui::SetItemAllowOverlap();
                ImGui::SetCursorPos(Position);
                //ImGui::InvisibleButton("##move_button", ImVec2(ImGui::GetItemRectSize().x, ImGui::GetItemRectSize().y));
                ImGui::InvisibleButton(FallBackLabel, ImVec2(ImGui::GetItemRectSize().x, ImGui::GetItemRectSize().y));
                if (ImGui::IsItemHovered())
                {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
                    // Change mouse cursor if not glfw because resize cursor not implemented
                }
                if (ImGui::IsItemClicked())
                {
                    Held = true;
                }
            }
            if (Held)
            {
                ImGui::SetTooltip("Moving component %s", Label.c_str());
                Position += ImGui::GetIO().MouseDelta;
                Held = true;
            }
            if (!ImGui::IsMouseDown(0))
            {
                Held = false;
            }
        }
    }

    void ImStructComponent::Editor()
    {
        ImGui::TextUnformatted(Label.c_str());
        ImGui::InputText("Label", &Label);
        if (Label.length() == 0)
        {
            Label = "default";
        }
        ImGui::SameLine();
        if (ImGui::Button("X"))
        {
            CanvasFlags &= ~CanvasFlags_Clicked;
        }
        ImGui::SameLine();
        if (ImGui::Button("DELETE"))
        {
            CanvasFlags |= CanvasFlags_Delete;
        }
        ImGui::DragFloat("Width", &Width, 1, 500);
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Width (only on some components) using ImGui::SetNextItemWidth(width)");
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Width (only on some components) using ImGui::SetNextItemWidth(width)");
        }
        ImGui::DragFloat2("Position Override", &Position.x, 1, 500);
        if (ImGui::CheckboxFlags("Override Position", &ComponentFlags, ComponentFlags_OverridePosition))
        {
            if (Position.x == 0 && Position.y == 0)
            {
                Position = CursorTemp;
            }
        }
        
        // same line bool that changes the component flags
        ImGui::CheckboxFlags("Same Line", &ComponentFlags, ComponentFlags_SameLine);
        ImGui::Text("Component Flags 0x%s", std::bitset<8>(ComponentFlags).to_string().c_str());
    }

    void ImStructComponent::DrawTree()
    {
        // create an imgui table that contains component flags and canvas flags so the row is text and flags
        if(ImGui::BeginTable("##Flags", 2, ImGuiTableFlags_NoBordersInBody))
        {
            const std::bitset<8> component_flags(ComponentFlags);
            const std::bitset<8> canvas_flags(CanvasFlags);
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Component Flags");
            ImGui::TableNextColumn();
            ImGui::Text("0x%s", component_flags.to_string().c_str());
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Canvas Flags");
            ImGui::TableNextColumn();
            ImGui::Text("0x%s", canvas_flags.to_string().c_str());
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    std::string ImStructComponent::Serialise() const
    {
        std::stringstream ss;
        
        ss << "ImStructComponent(";
        ImSerialise(ss, Label); ss << ", ";
        ImSerialise(ss, ComponentFlags); ss << ", ";
        ImSerialise(ss, Width); ss << ", ";
        ImSerialise(ss, Position); ss << ")";
        
        return ss.str();
    }

    void ImStructComponent::Deserialise(std::string str)
    {
        std::stringstream ss;

        if(str.find("ImStructComponent(") == 0) { // This gives us the ability to also just pass in the args
            std::erase(str, ',');
            ss << str.substr(18, str.length() - 2);
        }
        
        ImDeserialise(ss, Label);
        ImDeserialise(ss, ComponentFlags);
        ImDeserialise(ss, Width);
        ImDeserialise(ss, Position);
    }

    std::string ImStructComponent::Compile()
    {
        std::string result;
        if (Width != 0.0f)
        {
            result += "ImGui::SetNextItemWidth(" + std::to_string(Width) + "); ";
        }
        if (ComponentFlags & ComponentFlags_SameLine)
        {
            result += "ImGui::SameLine(); ";
        }
        return result;
    }
}
