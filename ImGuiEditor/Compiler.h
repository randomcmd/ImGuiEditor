#pragma once
#include <string>
#include <vector>

class CanvasContainer;

namespace CompilerFramework
{
    struct CodeFile;
    struct Compilable
    {
        virtual ~Compilable() = default;
        [[nodiscard]] virtual std::string Compile(const CodeFile* code_file = nullptr) const { return ""; }
    };

    struct CodeChunk : Compilable
    {
        std::vector<std::string> Lines;

    };

    struct Method : Compilable // TODO: CURRENLTY ONLY SUPPORTS VOID METHODS WITHOUT PARAMETERS
    {
        std::string Name;
        std::vector<CodeChunk*> LocalBuffers;
        std::vector<CodeChunk*> CodeChunks;
    };

    struct CodeFile
    {
        virtual ~CodeFile() = default;
        std::vector<CodeChunk*> GlobalBuffers;
        std::vector<Method*> Methods;
        [[nodiscard]] virtual std::string FullyCompile() const { return ""; }
    };

    class Compiler
    {
    public:
        Compiler() = default;
        virtual ~Compiler() = default;

        virtual std::string Compile(const CanvasContainer* root_canvas); // TODO: Add multi file support and difference between root and sub canvases
    };
}
