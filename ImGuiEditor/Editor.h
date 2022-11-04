#pragma once
#include "CanvasData.h"

namespace ImStructs
{
    struct ImStruct;
}

namespace ReMi
{
    void EditorWindow();
    void Canvas();
    bool CanvasDropTarget();
    void AddDropTargetToCanvas(size_t i); // TODO: This code is bad because it uses a lot of hard coded types
    //CanvasContainer canvas;
}
