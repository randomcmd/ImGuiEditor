#pragma once
#include "Compiler.h"

namespace Target
{
    struct CodeChunk : CompilerFramework::CodeChunk
    {
        std::string Compile(const CompilerFramework::CodeFile* code_file) const override;
    };

    struct Method : CompilerFramework::Method
    {
        std::string Compile(const CompilerFramework::CodeFile* code_file) const override;
    };

    struct CodeFile : CompilerFramework::CodeFile
    {
        [[nodiscard]] std::string FullyCompile() const override;
    };
    
    class Target : public CompilerFramework::Compiler
    {
    public:
        std::string Compile(const CanvasContainer* root_canvas) override;
    };
}