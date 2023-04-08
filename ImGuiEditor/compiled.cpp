#include "imgui.h"
#include "ImGuiExtension.h"

// COMPILED BY TARGET V1
void Gui()
{
	if(ImGui::ColoredButtonV1("Hello World##1", ImVec2(0.000000f, 0.000000f), ImColor(1.000000f, 1.000000f, 1.000000f, 1.000000f), ImColor(1.000000f, 0.941177f, 0.125490f, 0.627451f), ImColor(1.000000f, 0.596078f, 0.427451f, 0.160784f))) { /** TODO: Add code here for Hello World##1 **/ }
	if(ImGui::TreeNode("Hello Tree Node")) { /** TODO: Add code here for Hello Tree Node **/
		if(ImGui::ColoredButtonV1("Hello", ImVec2(0.000000f, 0.000000f), ImColor(1.000000f, 1.000000f, 1.000000f, 1.000000f), ImColor(1.000000f, 0.941177f, 0.125490f, 0.627451f), ImColor(1.000000f, 0.596078f, 0.427451f, 0.160784f))) { /** TODO: Add code here for Hello##2 **/ }		if(ImGui::ColoredButtonV1("World", ImVec2(0.000000f, 0.000000f), ImColor(1.000000f, 1.000000f, 1.000000f, 1.000000f), ImColor(1.000000f, 0.941177f, 0.125490f, 0.627451f), ImColor(1.000000f, 0.596078f, 0.427451f, 0.160784f))) { /** TODO: Add code here for World##3 **/ }		if(ImGui::ColoredButtonV1("HIIIIIIIIIIIIIIIIIII!", ImVec2(0.000000f, 0.000000f), ImColor(1.000000f, 1.000000f, 1.000000f, 1.000000f), ImColor(1.000000f, 0.941177f, 0.125490f, 0.627451f), ImColor(1.000000f, 0.596078f, 0.427451f, 0.160784f))) { /** TODO: Add code here for HIIIIIIIIIIIIIIIIIII!##4 **/ }
		ImGui::TreePop();
	}
}
