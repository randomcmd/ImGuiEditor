#include "CanvasData.h"

#include <filesystem>
#include <fstream>

#include "ComponentWrapper.h"
#include "Editor.h"

bool CanvasContainer::CanvasDropTarget(const size_t i, const ImStructs::CanvasFlags canvas_flags, const ImStructs::ComponentFlags component_flags)
{
    const auto mouse_cursor_pos = ImGui::GetMousePos();
    const auto cursor_pos = ImGui::GetCursorScreenPos();
    if(abs(mouse_cursor_pos.y - cursor_pos.y) > 7.5 ) return false;
    if(abs(mouse_cursor_pos.x - cursor_pos.x) > 100 ) return false;
    if(ImGui::GetDragDropPayload() == nullptr) return false;
    ImGui::BeginChild("addcomponent", ImVec2(100, 10));
    ImGui::EndChild();

    if(ImGui::BeginDragDropTarget())
    {
        AddDropTargetToCanvas(i, canvas_flags, component_flags);
        return true;
    }
    return false;
}

void CanvasContainer::AddDropTargetToCanvas(const size_t i, const ImStructs::CanvasFlags canvas_flags, const ImStructs::ComponentFlags component_flags)
{
    if(const auto payload = ImGui::AcceptDragDropPayload("component")) {
        const auto construct = *static_cast<ImStructs::ImGuiComponentFactory*>(payload->Data);
        auto component = construct();
        component->ComponentFlags = component_flags;
        component->CanvasFlags = canvas_flags;
        const auto iterator = ImStructs.begin() + static_cast<long long>(i);
        ImStructs.emplace(iterator, component);
    }
    if(const auto payload = ImGui::AcceptDragDropPayload(m_MoveType.c_str()))
    {
        // relocate old component
        auto componentIndex = *static_cast<size_t*>(payload->Data);
        const auto component = ImStructs.at(componentIndex).release();
        component->ComponentFlags = component_flags;
        component->CanvasFlags = canvas_flags;
        const auto it = ImStructs.begin() + i;

        if(componentIndex > i) // if we move it back
        {
            //it++;
            componentIndex++;
        }
        
        ImStructs.emplace(it, component);
        ImStructs.erase(ImStructs.begin() + componentIndex);
    }
}

void CanvasContainer::UpdateCanvasFlags()
{
    for (auto& component : ImStructs) // Applying canvas flags
    {
        if(component->CanvasFlags & ImStructs::CanvasFlags_Delete)
        {
            std::erase(ImStructs, component);
        }
    }
}

void CanvasContainer::Draw()
{
    UpdateCanvasFlags();
    CanvasDropTarget(0);
    
    // iterate through all the structs and draw them
    for(size_t i = 0; i < ImStructs.size(); i++)
    {
        const auto& component = ImStructs.at(i); 
        ImGui::PushID(&component);
        component->PreDraw();
        component->Draw();
        component->PostDraw();
        component->Cleanup();
        ImGui::PopID();
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
        if(ImGui::IsItemClicked()) component->CanvasFlags |= ImStructs::CanvasFlags_Clicked;
        if(ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        {
            std::string payload = "Hello Sannej!";
            ImGui::SetDragDropPayload(m_MoveType.c_str(), &i, sizeof(i));
            ImGui::SetTooltip("movingg component %s", component->Label.c_str());
            ImGui::EndDragDropSource();
        }

        // next component if it exists
        auto nextSameLine = false;
        auto thisSameLine = component->ComponentFlags & ImStructs::ComponentFlags_SameLine;
        auto previousSameLine = false;
        auto nextSameLineFlag = 0;
        auto previousSameLineFlag = 0;
        const auto& nextComponent = ImStructs.size() > i + 1 ? ImStructs.at(i + 1).get() : nullptr;
        const auto& previousComponent = i > 0 ? ImStructs.at(i - 1).get() : nullptr;
        if(nextComponent && nextComponent->ComponentFlags & ImStructs::ComponentFlags_SameLine)
        {
            nextSameLine = true;
            nextSameLineFlag = ImStructs::ComponentFlags_SameLine;
        }
        if(previousComponent && previousComponent->ComponentFlags & ImStructs::ComponentFlags_SameLine)
        {
            previousSameLine = true;
            previousSameLineFlag = ImStructs::ComponentFlags_SameLine;
        }

        // next same line? canvas drop target Canvas_Flags_NextSameLine
        // previous same line and the next one is either null or not next line? canvas drop target Canvas_Flags_NextSameLine
        // default? canvas drop target 0

        if(nextSameLine)
        {
            ImGui::SameLine();
            CanvasDropTarget(i + 1, ImStructs::CanvasFlags_None, ImStructs::ComponentFlags_SameLine);
        }
        else if(thisSameLine && !nextSameLineFlag)
        {
            ImGui::SameLine();
            if(!CanvasDropTarget(i + 1, ImStructs::CanvasFlags_None, ImStructs::ComponentFlags_SameLine)) ImGui::NewLine();
            CanvasDropTarget(i + 1, ImStructs::CanvasFlags_None, ImStructs::CanvasFlags_None);
        }
        else
        {
            CanvasDropTarget(i + 1, ImStructs::CanvasFlags_None, ImStructs::CanvasFlags_None);
        }
    }
}

void CanvasContainer::DrawTree(const bool in_new_window) const
// RECURSION VERY SCARY!!!!!!!!!!!!!
{
    if(in_new_window) {
        std::string window_name = "Canvas Tree View##";
        window_name += std::to_string(m_UUID);
        ImGui::Begin(window_name.c_str());
    }
    for(const auto& component : ImStructs)
    {
        ImGui::PushID(&component);
        if(ImGui::TreeNode(component->Label.c_str()))
        {
            std::bitset<8> component_flags(component->ComponentFlags);
            std::bitset<8> canvas_flags(component->CanvasFlags);
            ImGui::Text("Component Flags: 0x%s", component_flags.to_string().c_str());
            ImGui::Text("Canvas Flags:    0x%s", canvas_flags.to_string().c_str());
            if(dynamic_cast<ImStructs::ScopedImStruct*>(component.get()))
            {
                const auto scoped = dynamic_cast<ImStructs::ScopedImStruct*>(component.get());
                if(ImGui::TreeNode("Canvas")) {
                    if(ImGui::BeginDragDropTarget()) {
                        scoped->Canvas.AddDropTargetToCanvas(0);
                        ImGui::EndDragDropTarget();
                    }
                    scoped->Canvas.DrawTree(false);
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }
        ImGui::PopID();
    }

    if(in_new_window) {
        ImGui::End();
    }
}

void CanvasContainer::CompileCPP() const
{
    // Create a new file
    std::ofstream file;
    file.open("compiled.cpp");

    file << "#include <imgui.h>" << std::endl;
    file << "#include <imgui_stdlib.h>" << std::endl;
    file << "#include \"ImGuiExtension.h\"" << std::endl << std::endl;  // TODO: Temporary solution for extension imports. Should be added per component.

    file << "void Gui() {" << std::endl;
    
    // iterate through the canvas
    for(size_t i = 0; i < ImStructs.size(); i++)
    {
        file << "\t" << ImStructs[i]->Compile() << std::endl;          // TODO: Make this recursive
    }

    file << "}" << std::endl;
    file.close();
}

std::string CanvasContainer::Serialise() const
{
    std::stringstream ss;
    ss << "CanvasContainer##0000" << "(" << std::endl;
    for(const auto& component : ImStructs)
    {
        ss << "\t" << component->Serialise() << "," << std::endl;
    }
    ss << ");" << std::endl;
    return ss.str();
}

void CanvasContainer::Clear()
{
    ImStructs.clear();
}

void CanvasContainer::Deserialise(std::string string, ReMi::Editor& editor)
{
    Clear();
    const auto call = ImSerialisation::Call(string);
    for(const auto& param : call.Params) 
    {
        const auto inner_call = ImSerialisation::Call(param);
        auto component = editor.TemporaryConstructFromName(inner_call.FunctionName);
        assert(component && "Component not found in editor");
        component->ActiveIn = &editor;
        component->Deserialise(param);
        ImStructs.emplace_back(component.release());
    }
}

std::string CanvasContainer::Compile(CompilerFramework::Compiler* compiler) const
{
    
    return compiler->Compile(this);
}

void CanvasContainer::CompileToFile(CompilerFramework::Compiler* compiler, std::filesystem::path filepath) const
{
    // Create a new file
    std::ofstream file;
    file.open(filepath);
    file << Compile(compiler);
    file.close();
}
