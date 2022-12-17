#include <imgui.h>
#include <imgui_stdlib.h>
#include "ImGradient.h"

void Gui() {
   ImGui::TextUnformatted("Hello, world!");
   if(ImGui::Button("hej button")) { /** TODO: Add code for hej button **/ }
   ImGui::InputText("hej user input", &hej user inputbuf, 0, 0, 0);
   ImGui::TextUnformatted("default", nullptr);
   if(ImGui::InputText("default", true, 0, false, false)) { /** TODO: Add code here for default **/ }
   if(ImGui::SliderFloat("default", true, 0.000000, 1.000000, "", 1.000000)) { /** TODO: Add code here for default **/ }
   if(ImGui::ColoredButtonV1("default", ImVec2(0.000000, 0.000000), ImColor(1.000000, 1.000000, 1.000000, 1.000000), ImColor(1.000000, 0.941177, 0.125490, 0.627451), ImColor(1.000000, 0.596078, 0.427451, 0.160784))) { /** TODO: Add code here for default **/ }
   if(ImGui::ColoredButtonV1("default", ImVec2(0.000000, 0.000000), ImColor(1.000000, 1.000000, 1.000000, 1.000000), ImColor(1.000000, 0.941177, 0.125490, 0.627451), ImColor(1.000000, 0.596078, 0.427451, 0.160784))) { /** TODO: Add code here for default **/ }
}
