cmake_minimum_required(VERSION 3.26)
project(TekEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(TekEngine main.cpp
        Tek/Core/Config.hpp
        Tek/Shader.cpp
        Tek/Shader.hpp
        TekEngine.hpp
        Tek/Core/Logger.cpp
        Tek/Core/Logger.hpp
        Tek/External/stb_image.h)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(TekEngine PRIVATE glfw)
find_package(glad CONFIG REQUIRED)
target_link_libraries(TekEngine PRIVATE glad::glad)
find_package(imgui CONFIG REQUIRED)
target_link_libraries(TekEngine PRIVATE imgui::imgui)