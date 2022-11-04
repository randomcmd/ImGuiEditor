#pragma once
#include <vector>

#include "ImGuiStructs.h"

class CanvasContainer
{
public:
    std::vector<ImStructs::ImStruct*> m_ImStructs;

    void CompileCPP();
};
