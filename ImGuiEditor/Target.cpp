#include "Target.h"
#include <sstream>

#include "ImStructs.h"
#include "CanvasData.h"

std::string Target::CodeChunk::Compile(const CompilerFramework::CodeFile* code_file) const
{
    std::stringstream ss;
    for(auto& line : Lines)
    {
        ss << line;
    }
    return ss.str();
}

std::string Target::Method::Compile(const CompilerFramework::CodeFile* code_file) const
{
    std::stringstream ss;
    ss << "void " << Name << "()\n";
    ss << "{";
    for (auto& chunk : CodeChunks)
    {
        ss << chunk->Compile(code_file);
    }
    ss << "}";

    return ss.str();
}

std::string Target::CodeFile::FullyCompile() const
{
    std::stringstream ss;
    for (auto& method : Methods)
    {
        ss << method->Compile(this);
    }
    return ss.str();
}

std::string Target::Target::Compile(const CanvasContainer* root_canvas)
{
    std::stringstream code;
    code << "// COMPILED BY TARGET V1" << std::endl;

    CodeFile code_file;
    
    Method main;
    main.Name = "Gui";

    for (auto& canvas : root_canvas->ImStructs)
    {
        auto* chunk = new CodeChunk();
        chunk->Lines.emplace_back(canvas->Compile());
        main.CodeChunks.emplace_back(chunk);
    }

    code_file.Methods.emplace_back(&main);

    code << code_file.FullyCompile();

    return code.str();
}
