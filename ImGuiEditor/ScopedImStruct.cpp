#include "ImStructs.h"
#include "ComponentWrapper.h"
#include "Editor.h"

namespace ImStructs
{
    ScopedImStruct::ScopedImStruct(ImStructComponent* begin, ImStructComponent* end) : Begin(begin), End(end) {}

    void ScopedImStruct::Draw()
    {
        ImStructComponent::Draw();
        Begin->Draw();

        if (!CallEndOnlyIfBeginReturnsTrue) // LEGACY JUST CALLS THE DRAW EVEN IF BEGIN DOESN'T RETURN TRUE
        {
            Canvas.Draw();
            ImGui::SameLine();
            ImGui::SmallButton("Edit Scoped Struct"); // TODO: FIX THIS editing is broken for components that house multiple draw calls and "just drawing a child" doesn't work since the size is not obvious upfront
            End->Draw();
            return;
        }
        if (Begin && Begin->DrawReturn)
        {
            Canvas.Draw();
            ImGui::SameLine();
            ImGui::SmallButton("Edit Scoped Struct");
            End->Draw();
        }
    }

    void ScopedImStruct::Editor()
    {
        ImStructComponent::Editor();
        ImGui::PushID("##scoped_imstruct_begin");
        Begin->Editor();
        ImGui::PopID();
        
        if(ImGui::TreeNode("Open Canvas Components")) {
            // draw editor of all open components
            for (const auto& component : Canvas.ImStructs)
            {
                if (component->CanvasFlags & CanvasFlags_Clicked)
                {
                    ImGui::PushID(&component);
                    component->Editor();
                    ImGui::PopID();
                    ImGui::Separator();
                }
            }
            ImGui::TreePop();
        }
        
        ImGui::Separator();
        ImGui::PushID("##scoped_imstruct_end");
        End->Editor();
        ImGui::PopID();
    }

    void ScopedImStruct::PreDraw()
    {
        ImStructComponent::PreDraw();
        Begin->PreDraw();
        if (!CallEndOnlyIfBeginReturnsTrue)
        {
            End->PreDraw();
            return;
        }
        if (Begin && Begin->DrawReturn)
        {
            End->PreDraw();
        }
    }

    void ScopedImStruct::PostDraw()
    {
        ImStructComponent::PostDraw();
        Begin->PostDraw();
        if (!CallEndOnlyIfBeginReturnsTrue)
        {
            End->PostDraw();
            return;
        }
        if (Begin && Begin->DrawReturn)
        {
            End->PostDraw();
        }
    }

    void ScopedImStruct::Cleanup()
    {
        ImStructComponent::Cleanup();
        Begin->Cleanup();
        if (!CallEndOnlyIfBeginReturnsTrue)
        {
            End->Cleanup();
            return;
        }
        if (Begin && Begin->DrawReturn)
        {
            End->Cleanup();
        }
    }

    void ScopedImStruct::DrawTree()
    {
        if(ImGui::TreeNode(Label.c_str()))
        {
            const std::bitset<8> component_flags(ComponentFlags);
            const std::bitset<8> canvas_flags(CanvasFlags);
            ImGui::Text("Component Flags: 0x%s", component_flags.to_string().c_str());
            ImGui::Text("Canvas Flags:    0x%s", canvas_flags.to_string().c_str());
            if(ImGui::TreeNode("Canvas")) {
                if(ImGui::BeginDragDropTarget()) {
                    Canvas.AddDropTargetToCanvas(0);
                    ImGui::EndDragDropTarget();
                }
                Canvas.DrawTree(false);
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }

    std::string ScopedImStruct::Compile()
    {
        std::string code = ImStructComponent::Compile();
        if (!CallEndOnlyIfBeginReturnsTrue)
        {
            code += Begin->Compile();
            for (const auto& components : Canvas.ImStructs)
            {
                code += components->Compile();
            }
            code += "\n\t";
            code += End->Compile();
        }
        else
        {
            std::string begin = Begin->Compile();
            begin = begin.substr(0, begin.size() - 2);
            code += begin + "\n";
            for (const auto& components : Canvas.ImStructs)
            {
                code += "\t\t" + components->Compile();
            }
            code += "\n\t\t";
            code += End->Compile();
            code += "\n\t}";
        }
        return code;
    }

    std::string ScopedImStruct::Serialise() const
    {
        std::stringstream ss;
        ss << Name << "##69420(" << ImStruct::Serialise() << ", "<< Begin->Serialise() << ", " << End->Serialise() << ", " << CallEndOnlyIfBeginReturnsTrue << ", ";
        ss << Canvas.Serialise();
        // remove last comma
        std::string serialised = ss.str();
        serialised = serialised.substr(0, serialised.size() - 2);
        serialised += ")";
        return serialised;
    }

    void ScopedImStruct::Deserialise(std::string str)
    {
        ImSerialisation::Call call(str);
        assert(call.Params.size() == 5 && "ScopedImStruct::Deserialise: Incorrect number of parameters");
        Name = call.FunctionName;
        ImStruct::Deserialise(call.Params[0]);
        Begin->Deserialise(call.Params[1]);
        End->Deserialise(call.Params[2]);
        CallEndOnlyIfBeginReturnsTrue = std::stoi(call.Params[3]);
        Canvas.Deserialise(call.Params[4], *ActiveIn);
    }
}