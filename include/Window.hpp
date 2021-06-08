#ifndef WINDOW_H
#define WINDOW_H

#include "Exception.hpp"

#include <memory>
// #include <GL/gl3w.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    class InitWindowException : public Exception
    {
        using Exception::Exception;
    public:
        const char *GetType() const override { return "InitWindowException"; }
    };
public:
    Window();
    ~Window();
    bool IsRunning();
    void Render();
    GLFWwindow* GetRawWindow() const { return window; }
private:
    GLFWwindow* window;
};

#define INIT_WINDOW_EXCEPTION(msg) Window::InitWindowException(__LINE__, __FILE__, msg);

#endif
