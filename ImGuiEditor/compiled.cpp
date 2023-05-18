#include "ImGuiExtension.h"

ImString operator ""_im(const char* literal, size_t size)
{
    assert(literal[size] == '\0' && "String literal must be null-terminated");
    return { literal };
}

void Gui()
{
    auto imstring = "Hello"_im;
    // COMPILED BY TARGET V1
    // COMPILED BY TARGET V1
    ImGui::TextUnformatted("hi this is a header", nullptr /*nullptr_t*/);
    if(ImGui::ColoredButtonV1("Hello, Fancy Button!", ImVec2(0, 0), ImColor(1, 1, 1, 1), ImColor(1, 0.94117653, 0.1254902, 0.627451), ImColor(1, 0.59607846, 0.427451, 0.16078432))) { /** TODO: Add code here for Default##2 **/ }
}
