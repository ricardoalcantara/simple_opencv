#ifndef APP_H
#define APP_H

#include "Exception.hpp"

class GLFWwindow;

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
    void Initialize();
    void Run();
    void AddImGui();

private:
    GLFWwindow *window;

private:
    void RenderUI();
};

#define INIT_APP_EXCEPTION(msg) App::InitAppException(__LINE__, __FILE__, msg);

#endif
