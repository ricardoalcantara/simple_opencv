#include "Tracker.hpp"
#include <spdlog/spdlog.h>

int main(int argc, char const *argv[])
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Welcome to spdlog!");

    Tracker t = {};
    t.Initialize();
    t.Run();
    return 0;
}
