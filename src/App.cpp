#include "App.hpp"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <spdlog/spdlog.h>

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>

App::App()
{
    window = std::make_unique<Window>();
    // tracker = std::make_unique<Tracker>();
}

App::~App()
{
    if (ImGui::GetCurrentContext() != NULL)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

void App::AddImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window->GetRawWindow(), true);
    ImGui_ImplOpenGL3_Init(NULL);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void App::RenderUI()
{
    if (ImGui::GetCurrentContext() == NULL)
        return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::Button("Button"))
        {
            if (tracker.IsCapturing())
            {
                tracker.StopCapturing();
            }
            else
            {
                tracker.StartCapturing();
            }
        }
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::EndMainMenuBar();
    }

    if (ImGui::Begin("Capturing screen"))
    {
        void* t = reinterpret_cast<void*>(tracker.imageTexture.textureID);
        ImGui::Image(t, ImVec2(1920, 1080));
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void App::Run()
{
    while (window->IsRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        tracker.imageTexture.LoadBuffer();
        RenderUI();

        window->Render();
    }
}