#include "Editor.h"
#include <functional>
#include <imgui.h>
#include <string>
#include <vector>
#include "ImGradient.h"
#include "ImGuiStructs.h"

#define PREVIEW_LAST_COMPILE 1 // This is a temporary hack to import the compiled.cpp file

#if PREVIEW_LAST_COMPILE
#include "compiled.h"
#endif

CanvasContainer canvas; // TODO(faraway): Have different editor windows have different canvases and states for editing of multiple guis at the same time

using ImStructs::ImStruct;
using ImGuiComponentFactory = std::function<ImStruct*()>;

void ComponentButton(std::string_view label, const ImGuiComponentFactory* factory)
{
    if(ImGui::Button(label.data()))
    {
        canvas.m_ImStructs.push_back(factory->operator()());
    }

    if(ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("component", factory, sizeof(ImGuiComponentFactory));
        ImGui::SetTooltip("Adding %s", label.data());
        ImGui::EndDragDropSource();
    }
}

void ReMi::EditorWindow()
{
    ImGui::Begin("Hello, world!");

    ComponentButton("Add random text",
    new ImGuiComponentFactory([]() {
        return new ImStructs::Text();
    }));
    
    ComponentButton("Add random button",
    new ImGuiComponentFactory([](){
        const auto buttonData = new ImStructs::Button();
        buttonData->label = "hej button";
        return buttonData;
    }));

    ComponentButton("Add random input",
    new ImGuiComponentFactory([](){
        const auto inputTextData = new ImStructs::InputText();
        inputTextData->label = "hej user input";
        return inputTextData;
    }));

    ComponentButton("experimental component wrapper for text",
    new ImGuiComponentFactory([]()
    {
        return ImStructs::make_component_wrapper(&ImGui::TextUnformatted, (const char*) "Hello, world!", nullptr);
    }));
     
    ComponentButton("experimental component wrapper for input text",
    new ImGuiComponentFactory([]()
    {
        bool (*InputText)(const char*, std::string*, ImGuiInputTextFlags, ImGuiInputTextCallback, void*) = ImGui::InputText;
        return ImStructs::make_component_wrapper(std::function(InputText), (const char*) "Input Text In Me", (std::string*) new std::string("Buffer"), (ImGuiInputTextFlags)0, (ImGuiInputTextCallback)0, (void*)0);
    }));

    ComponentButton("experimental component wrapper for float slider",
    new ImGuiComponentFactory([]()
    {
        bool (*SliderFloat)(const char*, float*, float, float, const char*, float) = ImGui::SliderFloat;
        return ImStructs::make_component_wrapper(std::function(SliderFloat), (const char*) "Slider Float In Me", (float*) new float(0.0f), (float)0.0f, (float)1.0f, (const char*) new char[16] {0}, (float)1.0f);
    }));

    ComponentButton("experimental component wrapper for Gradient Button V1",
    new const ImGuiComponentFactory([](){
        bool (*ColoredButton)(const char*, const ImVec2&, unsigned int, unsigned int, unsigned int) = ImGui::ColoredButtonV1;
        return ImStructs::make_component_wrapper(std::function(ColoredButton), (const char*) "Gradient Button V1", (ImVec2&) *new ImVec2(100, 25), *new ImColor(1.0f, 1.0f, 1.0f, 1.0f), *new ImColor(0xA020F0FF), *new ImColor(0x296d98FF));
    }));
    
    bool showingEditor = false;
    for (size_t i = 0; i<canvas.m_ImStructs.size(); i++)
    {
        auto component = canvas.m_ImStructs[i];
        if(component->canvasFlags & ImStructs::CanvasFlags_Clicked)
        {
            ImGui::Separator();
            ImGui::PushID(component);
            component->Editor();
            ImGui::PopID();
            showingEditor = true;
        }
        if(component->canvasFlags & ImStructs::CanvasFlags_Delete)
        {
            std::erase(canvas.m_ImStructs, component);
            delete component;
        }
    }

    if(showingEditor)
    {
        ImGui::Separator();
    }
    static bool demo = false;
    ImGui::Checkbox("Demo", &demo);
    if (demo)
    {
        ImGui::ShowDemoWindow(&demo);
    }

    if(ImGui::Button("Compile"))
    {
        canvas.CompileCPP();
    }
    
    // can i anchor a buttom to the bottom of the window? a: no q: WAIT WHAT? a: yes, but you have to do it manually
    //ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 35); // remi you just didn't put it in the right function smh you put it in the slider editor or something LMAO
    //ImGui::SetCursorPosY(20); the button doesn't render why? a: because the cursor is at the top of the window

    // how would i make that the button is anchored to the right side of the screen? a: you can't, you have to do it manually
    //ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 80); // remi you just didn't put it in the right function smh you put it in the slider editor or something LMAO

    #if PREVIEW_LAST_COMPILE
    static bool previewLastCompile = true;
    ImGui::SameLine();
    ImGui::Checkbox("Preview last compile", &previewLastCompile);
    if(previewLastCompile) {
        ImGui::Begin("Preview Last Compile");
        Gui();
        ImGui::End();
    }
#endif
    
    ImGui::End();
}

void ReMi::Canvas()
{
    ImGui::Begin("Canvas");

    if(canvas.m_ImStructs.empty()) {
        if(CanvasDropTarget())
        {
            AddDropTargetToCanvas(0);
        }
    }
    
    // iterate through all the structs and draw them
    for(size_t i = 0; i < canvas.m_ImStructs.size(); i++)
    {
        if(CanvasDropTarget())
        {
            AddDropTargetToCanvas(0);
        }
        const auto component = canvas.m_ImStructs.at(i); 
        ImGui::PushID(component);
        component->Draw();
        ImGui::PopID();
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Click to edit");
        if(ImGui::IsItemClicked()) component->canvasFlags |= ImStructs::CanvasFlags_Clicked;
        if(ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
        {
            std::string payload = "Hello Sannej!";
            ImGui::SetDragDropPayload("move component", &i, sizeof(i));
            ImGui::SetTooltip("movingg component %s", component->label.c_str());
            ImGui::EndDragDropSource();
        }
        if(CanvasDropTarget())
        {
            AddDropTargetToCanvas(i + 1);
        }
    }
    
    ImGui::End();
}

bool ReMi::CanvasDropTarget()
{
    const auto mouseCursorPos = ImGui::GetMousePos();
    const auto cursorPos = ImGui::GetCursorScreenPos();
    if(abs(mouseCursorPos.y - cursorPos.y) > 10) return false;
    if(ImGui::GetDragDropPayload() == nullptr) return false;
    ImGui::BeginChild("addcomponent", ImVec2(100, 10));
    ImGui::EndChild();
    if(ImGui::BeginDragDropTarget())
    {
        ImGui::EndDragDropTarget();
        return true;
    }
    return false;
}

void ReMi::AddDropTargetToCanvas(size_t i)
{
    if(const auto payload = ImGui::AcceptDragDropPayload("component")) {
        const auto construct = *static_cast<ImGuiComponentFactory*>(payload->Data);
        ImStructs::ImStruct* component = construct();
        const auto iterator = canvas.m_ImStructs.begin() + static_cast<long long>(i);
        canvas.m_ImStructs.insert(iterator, component);
    }
    if(const auto payload = ImGui::AcceptDragDropPayload("move component"))
    {
        // relocate old component
        auto componentIndex = *static_cast<size_t*>(payload->Data);
        const auto component = canvas.m_ImStructs.at(componentIndex);
        const auto it = canvas.m_ImStructs.begin() + i;

        if(componentIndex > i) // if we move it back
        {
            //it++;
            componentIndex++;
        }
        
        canvas.m_ImStructs.insert(it, component);
        canvas.m_ImStructs.erase(canvas.m_ImStructs.begin() + componentIndex);
    }
}
