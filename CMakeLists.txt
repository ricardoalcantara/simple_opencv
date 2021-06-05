cmake_minimum_required(VERSION 3.0.0)
project(simple_opencv VERSION 0.1.0)

# set(BUILD_EXAMPLE OFF)
add_subdirectory(thirdparty)

# include(CTest)
# enable_testing()
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package (OpenCV 4.0.0 REQUIRED)
find_package (X11 REQUIRED)
find_package (Threads REQUIRED)

find_package (spdlog REQUIRED)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${PROJECT_NAME}
    include
    ./thirdparty/screen_capture_lite/include
)

add_executable(${PROJECT_NAME} src/main.cpp src/Tracker.cpp)

target_link_libraries(${PROJECT_NAME}
screen_capture_lite
spdlog::spdlog

${OpenCV_LIBS}

${X11_LIBRARIES}
${X11_Xfixes_LIB}
${X11_XTest_LIB}
${X11_Xinerama_LIB}

glfw ${GLFW_LIBRARIES}
OpenGL::GL

ImGui
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
