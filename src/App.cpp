#include "App.hpp"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <spdlog/spdlog.h>

// #include <GL/gl3w.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>

App::App()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        throw INIT_APP_EXCEPTION("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw INIT_APP_EXCEPTION("Failed to create GLFWwindow");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw INIT_APP_EXCEPTION("Failed to initialize GLFW");
    }
    // if (gl3wInit())
    // {
    //     spdlog::error("failed to initialize OpenGL");
    //     return -1;
    // }
    // if (!gl3wIsSupported(3, 2))
    // {
    //     spdlog::error("OpenGL 3.2 not supported");
    //     return -1;
    // }

    spdlog::info("OpenGL {}, GLSL {}", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
}

App::~App()
{
    if (ImGui::GetCurrentContext() != NULL)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    glfwTerminate();
}

void App::AddImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(NULL);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void App::RenderUI()
{
    if (ImGui::GetCurrentContext() == NULL)
        return;
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save"))
        spdlog::debug("Button Save clicked");

    // auto xxx = cv::imread("/home/ricardo/Projects/cpp/simple_opencv_image.jpg");
    // // cv::flip(xxx, xxx, 0);
    // GLuint textureTrash;
    // glGenTextures(1, &textureTrash);
    // glBindTexture(GL_TEXTURE_2D, textureTrash);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // // Set texture clamping method
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    // glTexImage2D(GL_TEXTURE_2D,     // Type of texture
    //                 0,                 // Pyramid level (for mip-mapping) - 0 is the top level
    //                 GL_RGB,            // Internal colour format to convert to
    //                 xxx.cols,          // Image width  i.e. 640 for Kinect in standard mode
    //                 xxx.rows,          // Image height i.e. 480 for Kinect in standard mode
    //                 0,                 // Border width in pixels (can either be 1 or 0)
    //                 GL_BGR, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
    //                 GL_UNSIGNED_BYTE,  // Image data type
    //                 xxx.ptr());        // The actual image data itself

    // glGenerateMipmap(GL_TEXTURE_2D);

    // ImGui::Image((void*)textureTrash, ImVec2(1920, 1080));
    // End of frame: render Dear ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void App::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        RenderUI();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
}