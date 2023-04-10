// glfw define 
#define GLFW_INCLUDE_NONE

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "glm/vec3.hpp"

#include "Editor.h"
#include "imgui/FreeTypeTest.h"
#include "misc/freetype/imgui_freetype.h"

// CHANGE THE IMCONFIG TO INCLUDE THE FOLLOWING PREPROCESSOR DEFINITIONS
#define IMGUI_ENABLE_FREETYPE
#define IMGUI_ENABLE_STB_TRUETYPE
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_USE_WCHAR32

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

    // enable dockspace
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Loading fonts
    io.Fonts->AddFontDefault();
    const auto inter = io.Fonts->AddFontFromFileTTF(R"(resources\Inter-Regular.ttf)", 16.0f);
    static ImWchar ranges[] = {static_cast<ImWchar>(0x1), static_cast<ImWchar>(0x1FFFF), static_cast<ImWchar>(0)};
    static ImFontConfig cfg;
    cfg.OversampleH = cfg.OversampleV = 1;
    cfg.MergeMode = true;
    cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_LoadColor;
    io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\seguiemj.ttf)", 16.0f, &cfg, ranges);
    io.FontDefault = inter;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    
    const glm::vec3 clear_color = {32.0 / 255.0, 32.0 / 255.0, 32.0 / 255.0};
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);

    ReMi::Editor editor;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glViewport(0, 0, 1500, 1000);
        glClear(GL_COLOR_BUFFER_BIT);

        // setup imgui that can close the window
        editor.PreNewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        const ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

        editor.Render();

        ImGui::Render();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            auto glfwContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(glfwContext);
        }
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
