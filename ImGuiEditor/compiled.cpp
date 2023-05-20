#include "ImGuiExtension.h"

ImString operator ""_im(const char* literal, size_t size)
{
    assert(literal[size] == '\0' && "String literal must be null-terminated");
    return { literal };
}

void Gui()
{
    ImGui::TextUnformatted("Hej Yan, welcome to your first ImGuiEditor project!", nullptr /*nullptr_t*/);
    if(ImGui::InputTextWithHint("Hello, World!", "Click on any component to edit it", new std::string(""), 0, nullptr /*ImGuiInputTextCallback*/, nullptr /*void**/)) { /** TODO: Add code here for Text **/ }
    if(ImGui::Button("Edit me!", ImVec2(0, 0))) { /** TODO: Add code here for EditMeButton **/ }
    ImGui::TextUnformatted("Drag a component onto the canvas from the window on the right", nullptr /*nullptr_t*/);
    if(ImGui::TreeNode("Click to open scoped component!")) { /** TODO: Add code here for Default **/
        if(ImGui::ColoredButtonV1("What't this? A fancy gradient button?", ImVec2(0, 0), ImColor(ImVec4{1, 1, 1, 1}), ImColor(ImVec4{1, 0.941177, 0.12549, 0.627451}), ImColor(ImVec4{1, 0.596078, 0.427451, 0.160784}))) { /** TODO: Add code here for fancy_button **/ }
        ImGui::TreePop();
    }
    ImGui::TextUnformatted("Any gui you create can be saved to a human readable .lay file for opening and editing later!", nullptr /*nullptr_t*/);
    ImGui::TextUnformatted("When you're done editing this file you can compile it!", nullptr /*nullptr_t*/);
    ImGui::TextUnformatted("Thank you so much for taking the time to look at my project c: Have fun looking around the program and code!", nullptr /*nullptr_t*/);
}
