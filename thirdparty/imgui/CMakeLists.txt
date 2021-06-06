project(ImGui)

# Compile as static library 
add_library(${PROJECT_NAME} STATIC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

target_compile_definitions(${PROJECT_NAME} PUBLIC PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_include_directories(${PROJECT_NAME}
PUBLIC ./
BUILD_INTERFACE ./imgui
)

target_link_libraries(${PROJECT_NAME} glad)