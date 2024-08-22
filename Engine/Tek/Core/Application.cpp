#include <memory>
#include "Application.hpp"

float Application::deltaTime = 0.0f;

Application::Application() {
    stbi_set_flip_vertically_on_load(true);

    Init();
}

Application::~Application() {
    Cleanup();
}

void Application::Init() {
    m_Window = std::make_shared<Window>(800, 600, "Game Engine");

    TestSceneSetup();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    SceneManager::GetActiveScene()->renderManager->Initialize();
}

void Application::Run() {
    MainLoop();
}

void Application::Cleanup() {
    glfwTerminate();
}

void Application::MainLoop() {
    while (!m_Window->ShouldClose()) {
        try {
            // per-frame time logic
            // --------------------
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            // -----
            m_Window->PollEvents();

            // render
            // ------

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


            SceneManager::GetActiveScene()->UpdateScene(deltaTime);
            SceneManager::GetActiveScene()->renderManager->Render();



            m_Window->SwapBuffers();
            glfwPollEvents();
        }
        catch(std::exception& e){
            std::cerr << "Caught: " << e.what() << std::endl;
        }
    }
}

void Application::TestSceneSetup() {
    //char path[] = "../Tek/Models/StandardCube/StandardCube.gltf";
    //char path[] = "../Tek/Models/Main.1_Sponza/NewSponza_Main_glTF_002.gltf";
    char path[] = "../Tek/Models/SPHERES/untitled.gltf";

    std::shared_ptr<GameObject> backPack = std::make_shared<GameObject>();

    m_Scene = SceneManager::GetActiveScene();

    m_Scene->AddGameObject(backPack);
    Model::LoadModelToGameObject(path, backPack);
    m_Scene->PrintSceneHierarchy();

//    std::shared_ptr<GameObject> cube = std::make_shared<GameObject>();
//    scene->AddGameObject(cube);
//    Model::LoadModelToGameObject(path, cube);
////
//    cube->GetTransform()->localPosition = glm::vec3(0.0f, 7.5f, 0.0f);
//    cube->GetTransform()->localScale = glm::vec3(0.5f, 0.5f, 0.5f);
//    cube->GetTransform()->localRotation.setFromEulerAngles(0.0f, 12.5f, 0.0f);

    backPack->GetTransform()->localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    backPack->GetTransform()->localScale = glm::vec3(0.5f, 0.5f, 0.5f);

    std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
    std::shared_ptr<Light> lightComponent = std::make_shared<Light>(Point, 3, glm::vec3(300.0f, 300.0f, 300.0f));
    m_Scene->AddGameObject(light);
    light->AddComponent<Light>(lightComponent);
    light->GetTransform()->localPosition = glm::vec3(-7, 3, 3);
    m_Scene->lightManager->AddLight(lightComponent);

    std::shared_ptr<GameObject> light2 = std::make_shared<GameObject>();
    std::shared_ptr<Light> lightComponent2 = std::make_shared<Light>(Point, 3, glm::vec3(30.0f, 300.0f, 30.0f));
    m_Scene->AddGameObject(light2);
    light2->AddComponent<Light>(lightComponent2);
    light2->GetTransform()->localPosition = glm::vec3(-5, 4, 3);
    m_Scene->lightManager->AddLight(lightComponent2);

    std::shared_ptr<GameObject> light4 = std::make_shared<GameObject>();
    std::shared_ptr<Light> lightComponent4 = std::make_shared<Light>(Directional, 10, glm::vec3(10, 10, 10));
    m_Scene->AddGameObject(light4);
    light4->AddComponent<Light>(lightComponent4);
    light4->GetTransform()->localRotation.setFromEulerAngles(90, 0, 0);
    m_Scene->lightManager->AddLight(lightComponent4);
}
