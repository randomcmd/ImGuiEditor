#include "CanvasData.h"

#include <fstream>

void CanvasContainer::CompileCPP()
{
    // Create a new file
    std::ofstream file;
    file.open("compiled.cpp");

    file << "void Gui() {" << std::endl;
    
    // iterate through the canvas
    for(size_t i = 0; i < m_ImStructs.size(); i++)
    {
        file << "   " << m_ImStructs[i]->Compile() << std::endl;
    }

    file << "}" << std::endl;
    file.close();
}
