#include "ComponentWrapper.h"
#include "Editor.h"
#include "ImStructs.h"

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
        ss << Name << "##69420(" << Begin->Serialise() << ", " << End->Serialise() << ", " << CallEndOnlyIfBeginReturnsTrue << ", ";
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
        assert(call.Params.size() == 4 && "ScopedImStruct::Deserialise: Invalid number of parameters");
        Name = call.FunctionName;
        Begin->Deserialise(call.Params[0]);
        End->Deserialise(call.Params[1]);
        CallEndOnlyIfBeginReturnsTrue = std::stoi(call.Params[2]);
        Canvas.Deserialise(call.Params[3], *ActiveIn);
    }
}