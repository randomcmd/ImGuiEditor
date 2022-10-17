// glfw define 
#define GLFW_INCLUDE_NONE
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/vec3.hpp>

#include "Editor.h"

int main()
{
    // Setup GLFW and ImGui
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(1500, 1000, "ImGui GLFW OpenGL3 example", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // init glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Setup ImGui binding
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    // enable dockspace
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    // Setup style
    ImGui::StyleColorsDark();
    
    static glm::vec3 clearColor = {0.69f, 0.42f, 0.96f};
    glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
    
    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glViewport(0, 0, 1500, 1000);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // setup imgui that can close the window
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);
        ReMi::EditorWindow();
        ReMi::Canvas();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    } // why isn't this working? Answer: I forgot to call glfwSwapBuffers

    // shtudown imgui and glfw
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    
    return 0;
}
