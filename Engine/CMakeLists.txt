cmake_minimum_required(VERSION 3.26)
project(TekEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(TekEngine main.cpp
        Tek/Core/Config.hpp
        Tek/Core/Rendering/Shader.cpp
        Tek/Core/Rendering/Shader.hpp
        TekEngine.hpp
        Tek/Core/Logger.cpp
        Tek/Core/Logger.hpp
        Tek/External/stb_image.h
        Tek/Core/GameObject.cpp
        Tek/Core/GameObject.hpp
        Tek/Core/Components/Transform.cpp
        Tek/Core/Components/Transform.hpp
        Tek/Core/Math.hpp
        Tek/Core/Math/Quaternion.cpp
        Tek/Core/Math/Quaternion.hpp
        Tek/Core/Components/Component.cpp
        Tek/Core/Components/Component.hpp
        Tek/Core/Scene.cpp
        Tek/Core/Scene.hpp
        Tek/Core/EditorCamera.cpp
        Tek/Core/EditorCamera.hpp
        Tek/Core/Rendering/Mesh.cpp
        Tek/Core/Rendering/Mesh.hpp
        Tek/Core/Rendering/Mesh.hpp
        Tek/Core/Rendering/Model.cpp
        Tek/Core/Rendering/Model.hpp
        Tek/Core/Rendering/Rendering.hpp
        Tek/Core/Components/Renderer.cpp
        Tek/Core/Components/Renderer.hpp
        Tek/Core/Audio/AudioManager.cpp
        Tek/Core/Audio/AudioManager.hpp
        Tek/Core/Rendering/LightManager.cpp
        Tek/Core/Rendering/LightManager.hpp
        Tek/Core/Components/Light.cpp
        Tek/Core/Components/Light.hpp
        Tek/Core/Rendering/RenderManager.cpp
        Tek/Core/Rendering/RenderManager.hpp
        Tek/Core/SceneManager.cpp
        Tek/Core/SceneManager.hpp
        Tek/Core/Rendering/Material.cpp
        Tek/Core/Rendering/Material.hpp
        Tek/Core/Application.cpp
        Tek/Core/Application.hpp
        Tek/Core/Window.cpp
        Tek/Core/Window.hpp)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(TekEngine PRIVATE glfw)
find_package(glad CONFIG REQUIRED)
target_link_libraries(TekEngine PRIVATE glad::glad)
find_package(imgui CONFIG REQUIRED)
target_link_libraries(TekEngine PRIVATE imgui::imgui)
find_package(glm CONFIG REQUIRED)
target_link_libraries(TekEngine PRIVATE glm::glm)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(TekEngine PRIVATE assimp::assimp)