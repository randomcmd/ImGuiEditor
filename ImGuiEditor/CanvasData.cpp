#include "CanvasData.h"

#include <filesystem>
#include <fstream>

#include "ImStructs.h"
#include "ComponentWrapper.h"
#include "Editor.h"
#include "Compiler.h"

CanvasContainer::CanvasContainer() : m_UUID(rand()) { }

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
        component->ActiveIn = &Editor();
        component->EditorLabel += std::format("##{}", Editor().ComponentID());
        const auto iterator = ImStructs.begin() + static_cast<long long>(i);
        ImStructs.emplace(iterator, component);
    }
    if(const auto payload = ImGui::AcceptDragDropPayload(m_MoveType.c_str()))
    {
        // relocate old component
        const auto componentIndex = *static_cast<size_t*>(payload->Data);
        const auto component = ImStructs.at(componentIndex).get();
        component->ComponentFlags = component_flags;
        component->CanvasFlags = canvas_flags;
        MoveComponent(componentIndex, i);
    }
}

void CanvasContainer::UpdateCanvasFlags()
{
    for (size_t i = 0; i < ImStructs.size(); i++) // Applying canvas flags
    {
        const auto& component = ImStructs.at(i);
        if(component->CanvasFlags & ImStructs::CanvasFlags_Delete)
        {
            std::erase(ImStructs, component);
        }
    }
}

void CanvasContainer::AddComponent(ImStructUPtr component)
{
    ImStructs.emplace_back(component.release());
    ImStructs.back()->EditorLabel += std::format("##{}", Editor().ComponentID());
    ImStructs.back()->ActiveIn = &Editor();
}

void CanvasContainer::MoveComponent(size_t origin, size_t destination)
{
    const auto component = ImStructs.at(origin).release();
    const auto it = ImStructs.begin() + destination;
    if(origin >= destination) // if we move it back
    {
        //it++;
        origin++;
    }
    ImStructs.emplace(it, component);
    ImStructs.erase(ImStructs.begin() + origin);
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
        if(ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        {
            std::string payload = "Hello Sannej!";
            ImGui::SetDragDropPayload(m_MoveType.c_str(), &i, sizeof(i));
            ImGui::SetTooltip("Movingg Component %s", component->EditorLabel.c_str());
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

void CanvasContainer::DrawTree() const
// RECURSION VERY SCARY!!!!!!!!!!!!!
{
    for (const auto& component : ImStructs)
    {
        const auto opened = ImGui::TreeNode(component->EditorLabel.c_str());
        if(ImGui::BeginPopupContextItem())
        {
            if(ImGui::MenuItem("Open"))
            {
                component->CanvasFlags |= ImStructs::CanvasFlags_Clicked;
            }
            // push text color red
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(8.0f, 0.3f, 0.4f, 1.0f));
            if(ImGui::MenuItem("Delete"))
            {
                component->CanvasFlags |= ImStructs::CanvasFlags_Delete;
            }
            ImGui::EndPopup();
            // pop text color
            ImGui::PopStyleColor();
        }
        if(opened)
        {
            ImGui::PushID(&component);
            component->DrawTree();
            ImGui::PopID();
        }
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
    for (const auto& ImStruct : ImStructs)
    {
        file << "\t" << ImStruct->Compile() << std::endl;
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
        const auto param_call = ImSerialisation::Call(param);
        auto component = editor.TemporaryConstructFromName(param_call.FunctionName);
        if(!component) {
            std::cout << "Component " << param_call.FunctionName << " not found in editor" << std::endl;
            assert(component && "Component not found in editor");
        }
        component->ActiveIn = &editor;
        component->Deserialise(param);
        ImStructs.push_back(std::move(component));
    }
}

ReMi::Editor& CanvasContainer::Editor() const
{
    return *ActiveIn->ActiveIn;
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
