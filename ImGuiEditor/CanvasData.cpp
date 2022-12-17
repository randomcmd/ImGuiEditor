#include "CanvasData.h"

#include <fstream>

void CanvasContainer::CompileCPP() const
{
    // Create a new file
    std::ofstream file;
    file.open("compiled.cpp");

    file << "#include <imgui.h>" << std::endl;
    file << "#include <imgui_stdlib.h>" << std::endl;
    file << "#include \"ImGradient.h\"" << std::endl << std::endl;

    file << "void Gui() {" << std::endl;
    
    // iterate through the canvas
    for(size_t i = 0; i < ImStructs.size(); i++)
    {
        file << "   " << ImStructs[i]->Compile() << std::endl;
    }

    file << "}" << std::endl;
    file.close();
}
