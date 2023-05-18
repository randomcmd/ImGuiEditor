#include "ImStructs.h"
#include "ComponentWrapper.h"
#include "Editor.h"

namespace ImStructs
{
    ScopedImStruct::ScopedImStruct(ImStructComponent* begin, ImStructComponent* end) : Begin(begin), End(end)
    {
        Canvas.ActiveIn = this;
    }

    void ScopedImStruct::Draw()
    {
        Begin->Draw();
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
        if(ImGui::IsItemClicked()) CanvasFlags |= ImStructs::CanvasFlags_Clicked;
        
        if (!CallEndOnlyIfBeginReturnsTrue) // LEGACY JUST CALLS THE DRAW EVEN IF BEGIN DOESN'T RETURN TRUE
        {
            Canvas.Draw();
            End->Draw();
            return;
        }
        if (Begin && Begin->DrawReturn)
        {
            Canvas.Draw();
            End->Draw();
        }
    }

    void ScopedImStruct::Editor()
    {
        ImGui::TextUnformatted(EditorLabel.c_str());
        ImGui::InputText("Label", &EditorLabel);
        if (EditorLabel.length() == 0)
        {
            EditorLabel = "default";
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
        if(ImGui::TreeNodeEx("Begin", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::PushID("##scoped_imstruct_begin");
            Begin->Editor();
            ImGui::PopID();
            ImGui::TreePop();
        }
        if(ImGui::TreeNodeEx("Open Canvas Components", ImGuiTreeNodeFlags_DefaultOpen))
        {
            // draw editor of all open components
            for (size_t i = 0; i < Canvas.ImStructs.size(); i++)
            {
                const auto& component = Canvas.ImStructs.at(i);
                if (component->CanvasFlags & CanvasFlags_Clicked)
                {
                    ImGui::PushID(&component);
                    component->Editor();
                    ImGui::PopID();
                    if(i != Canvas.ImStructs.size() - 1 && Canvas.ImStructs.at(i)->CanvasFlags & ImStructs::CanvasFlags_Clicked) {
                        ImGui::Separator();
                    }
                }
            }
            ImGui::TreePop();
        }
        if(ImGui::TreeNodeEx("End", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::PushID("##scoped_imstruct_end");
            End->Editor();
            ImGui::PopID();
            ImGui::TreePop();
        }
    }

    void ScopedImStruct::PreDraw()
    {
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
        const auto opened = ImGui::TreeNode("Canvas");
        if(ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("Drag and drop components here");
        }
        if(ImGui::BeginDragDropTarget()) {
            Canvas.AddDropTargetToCanvas(0);
            ImGui::EndDragDropTarget();
        }
        if(opened) {
            Canvas.DrawTree();
            ImGui::TreePop();
        }
    }

    std::string ScopedImStruct::Compile()
    {
        std::string code;
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