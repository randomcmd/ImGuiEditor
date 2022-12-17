#pragma once
#include "CanvasData.h"

namespace ImStructs
{
    struct ImStruct;
}

/* Alpha 1.0 Feature List
 *
 * ImGuiEditor:
 * [1] Add basic GUI
 * [1] Viewports
 * [1] Docking
 *  
 * Canvas:
 * [1] Basic canvas functionality
 * [0] Recursive canvases
 * [0] Canvas data
 *
 * Component Editor:
 * [1] Basic component editor functionality
 *
 * Templates:
 * [0] Template compilation
 * [0] Template parameter naming
 */

namespace ReMi
{
    void EditorWindow();
    void Canvas();
    bool CanvasDropTarget();
    void AddDropTargetToCanvas(size_t i);
    //CanvasContainer canvas;
}
