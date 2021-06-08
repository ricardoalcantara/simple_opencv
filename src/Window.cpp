#include "Window.hpp"

#include <spdlog/spdlog.h>

Window::Window()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        throw INIT_WINDOW_EXCEPTION("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        throw INIT_WINDOW_EXCEPTION("Failed to create GLFWwindow");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw INIT_WINDOW_EXCEPTION("Failed to initialize GLFW");
    }

    spdlog::info("OpenGL {}, GLSL {}", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
}
Window::~Window()
{
    glfwTerminate();
}
    
bool Window::IsRunning()
{
    return !glfwWindowShouldClose(window);
}

void Window::Render()
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();
}