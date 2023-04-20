#pragma once
#include <filesystem>
#include <memory>
#include <string>
#include <vector>
#include "imgui.h"

namespace ImStructs
{
    struct ImStruct;
    using CanvasFlags = int;
    using ComponentFlags = int;
    using ImStructUPtr = std::unique_ptr<ImStruct>;
}


namespace CompilerFramework
{
    class Compiler;
}

namespace ReMi
{
    class Editor;
}

class CanvasContainer
{
public:
    explicit CanvasContainer();

    std::vector<ImStructs::ImStructUPtr> ImStructs;
    std::optional<ImGuiStyle> m_ImGuiStyle;
    ImStructs::ImStruct* ActiveIn = nullptr;
    
    bool CanvasDropTarget(size_t i, ImStructs::CanvasFlags canvas_flags = 0, ImStructs::ComponentFlags component_flags = 0);
    void AddDropTargetToCanvas(size_t i, ImStructs::CanvasFlags canvas_flags = 0, ImStructs::ComponentFlags component_flags = 0);
    void UpdateCanvasFlags();

    void Draw();
    void DrawTree() const;
    void CompileCPP() const;
    [[nodiscard]] std::string Serialise() const;
    void Clear();
    void Deserialise(std::string string, ReMi::Editor& editor);

    using Compiler = CompilerFramework::Compiler;
    std::string Compile(Compiler* compiler) const;
    void CompileToFile(CompilerFramework::Compiler* compiler, std::filesystem::path filepath) const;

private:
    std::size_t m_UUID;
    std::string m_MoveType = std::string("move component##") + std::to_string(m_UUID); // TODO: this removes cross canvas dragging of components until implemeted
};