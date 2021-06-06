#include <spdlog/spdlog.h>

#include "App.hpp"

int main(int argc, char const *argv[])
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Welcome to Simple OpenCV!");

    try
    {
        App app = {};
        app.AddImGui();
        app.Run();
    }
    catch(const std::exception& e)
    {
        spdlog::error(e.what());
    }

    return 0;
}