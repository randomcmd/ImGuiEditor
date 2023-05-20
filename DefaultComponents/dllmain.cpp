#include "../ImGuiEditor/plugin/Plugin.h"

#include "Components.h"
#include "DragAndSliders.h"
#include "Inputs.h"
#include "ColorAndMisc.h"
#include "ScopedComponents.h"
#include "Trees.h"

inline int add(int a, int b)
{
    return a + b;
}

extern "C" __declspec(dllexport) Plugin* create(ImGuiContext* context, ImGuiMemAllocFunc allocFunc,
    ImGuiMemFreeFunc freeFunc)
{
    auto plugin = new Plugin();
    ImGui::SetCurrentContext(context);
    ImGui::SetAllocatorFunctions(allocFunc, freeFunc);
    plugin->PluginSpecs = {
        .Name = "Default Components",
        .Version = "0.1.0",
        .Author = "ReMi",
        .Description = "Most of the default ImGui components",
        .Github = "https://www.github.com/randomcmd/ImGuiEditor"
    };

    plugin->ComponentMaps = 
    {
        {
            "Components", 
            {
                    { "Text", Text },
                    { "Text Separator##SeparatorText", TextSeparator },
                    { "Button", Button },
                    { "Colored Button##ColoredButtonV1", ColoredButtonV1 },
                    { "Small Button##SmallButton", SmallButton },
                    { "Invisible Button##InvisibleButton", InvisibleButton },
                    { "Arrow Button##ArrowButton", ArrowButton },
                    { "Checkbox", Checkbox },
                    { "Radio Button##RadioButton", RadioButton },
                    { "Progress Bar##ProgressBar", ProgressBar },
                    { "Bullet", Bullet },
                    { "Text with bool##ValueBool", ValueBool },
                    { "Text with int##ValueInt", ValueInt },
                    { "Text with uint##ValueUInt", ValueUnsignedInt },
                    { "Text with float##ValueFloat", ValueFloat }
            }
        },
        {
            "Sliders and Drag Components",
            {
                { "Drag Float##DragFloat", DragFloat },
                { "Drag Float2##DragFloat2", DragFloat2 },
                { "Drag Float3##DragFloat3", DragFloat3 },
                { "Drag Float4##DragFloat4", DragFloat4 },
                // { "Drag Float Range2##DragFloatRange2", DragFloatRange2 } DOES NOT COMPILE
                { "Drag Int##DragInt", DragInt },
                { "Drag Int2##DragInt2", DragInt2 },
                { "Drag Int3##DragInt3", DragInt3 },
                { "Drag Int4##DragInt4", DragInt4 },
                // { "Drag Int Range2##DragIntRange2", DragIntRange2 }, DOES NOT COMPILE
                { "Slider Float##SliderFloat", SliderFloat },
                { "Slider Float2##SliderFloat2", SliderFloat2 },
                { "Slider Float3##SliderFloat3", SliderFloat3 },
                { "Slider Float4##SliderFloat4", SliderFloat4 },
                { "Slider Angle##SliderAngle", SliderAngle },
                { "Slider Int##SliderInt", SliderInt },
                { "Slider Int2##SliderInt2", SliderInt2 },
                { "Slider Int3##SliderInt3", SliderInt3 },
                { "Slider Int4##SliderInt4", SliderInt4 },
                { "Vertical Slider Float##VSliderFloat", VSliderFloat },
                { "Vertical Slider Int##VSliderInt", VSliderInt },
            }
        },
        {
            "Inputs",
            {
                { "Input Text##InputTextString", InputTextStdString },
                { "Input TextMultiline##InputTextMultilineString", InputTextMultilineStdString },
                { "Input TextWithHint##InputTextWithHintString", InputTextWithHintStdString },
                { "Input Float##InputFloat", InputFloat },
                { "Input Float2##InputFloat2", InputFloat2 },
                { "Input Float3##InputFloat3", InputFloat3 },
                { "Input Float4##InputFloat4", InputFloat4 },
                { "Input Int##InputInt", InputInt },
                { "Input Int2##InputInt2", InputInt2 },
                { "Input Int3##InputInt3", InputInt3 },
                { "Input Int4##InputInt4", InputInt4 },
                { "Input Double##InputDouble", InputDouble },
                // { "Input Scalar N", InputScalarN },
                // { "Input Text using const char*##InputText", InputText },
                // { "Input Text Multiline using const char*##InputTextMultiline", InputTextMultiline },
                // { "Input Text With Hint using const char*##InputTextWithHint", InputTextWithHint },
            }
        },
        {
            "Colors and misc",
            {
                { "Color Edit3##ColorEdit3", ColorEdit3 },
                { "Color Edit4##ColorEdit4", ColorEdit4 },
                { "Color Picker3##ColorPicker3", ColorPicker3 },
                { "Color Picker4##ColorPicker4", ColorPicker4 },
                { "Color Button##ColorButton", ColorButton },
                // { "Selectable using bool##Selectable", Selectable }, DEP
                // { "Selectable using bool*##SelectableWithPointer", SelectableWithPointer }
            }
        },
        {
            "Scoped Components",
            {
                { "Combo", Combo },
                { "List Box##ListBox", ListBox },
                // { "Menu Bar##MenuBar", MenuBar }, DOESNT WORK
                { "Menu", Menu },
                // { "Child", Child },
            }
        },
        {
            "Trees and Headers",
            {
                { "Tree Node##TreeNode", TreeNode },
                { "Tree Node with Flags##TreeNodeEx", TreeNodeEx },
                { "Collapsing Header##CollapsingHeader", CollapsingHeader }
            }
        }
    };
        
    return plugin;
}
            