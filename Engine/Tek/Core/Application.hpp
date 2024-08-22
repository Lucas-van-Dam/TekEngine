#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Rendering/stb_img_wrapper.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "SceneManager.hpp"
#include <memory>
#include "Window.hpp"

class Application {
public:
    Application();
    ~Application();

    void Run();

    static float deltaTime;

private:
    void Init();
    void MainLoop();
    void Cleanup();

    void TestSceneSetup();

    std::shared_ptr<Window> m_Window;
    std::shared_ptr<Scene> m_Scene;

    float lastFrame;
};


#endif //APPLICATION_HPP
