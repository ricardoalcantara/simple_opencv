#ifndef APP_H
#define APP_H

#include "Exception.hpp"
#include "Window.hpp"
#include "Tracker.hpp"

#include <memory>

// #include <GL/gl3w.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App
{
public:
    class InitAppException : public Exception
    {
        using Exception::Exception;
    public:
        const char *GetType() const override { return "InitAppException"; }
    };

public:
    App();
    ~App();
    void Run();
    void AddImGui();

private:
    std::unique_ptr<Window> window;
    Tracker tracker;

private:
    void RenderUI();
};

#define INIT_APP_EXCEPTION(msg) App::InitAppException(__LINE__, __FILE__, msg);

#endif
