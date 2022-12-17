#pragma once
#include <vector>

#include "ImGuiStructs.h"

class CanvasContainer
{
public:
    std::vector<ImStructs::ImStruct*> ImStructs;

    void CompileCPP() const;
};
