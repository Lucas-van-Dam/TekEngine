#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Tek/Core/Rendering/Shader.hpp"
#include "TekEngine.hpp"
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "Tek/External/stb_image.h"
#include "Tek/Core/EditorCamera.hpp"
#include "Tek/Core/Rendering/Model.hpp"
#include "Tek/Core/Scene.hpp"
#include "Tek/Core/Components/Renderer.hpp"
#include "Tek/Core/Audio/AudioManager.hpp"
#include "Tek/Core/SceneManager.hpp"

__declspec(dllexport) DWORD NvOptimusEnablement = 0x0000001;

float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = config::SCR_WIDTH / 2.0f;
float lastY = config::SCR_HEIGHT / 2.0f;

std::shared_ptr<EditorCamera> camera = std::make_shared<EditorCamera>(glm::vec3(-5.0f, 1.0f, 1.0f));
std::unique_ptr<SceneManager> sceneManager = std::make_unique<SceneManager>();

GLFWwindow *window;

bool reloadedShaders = false;
bool buttonPressed = false;
bool mouseLocked = true;

bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    camera->ProcessShiftKey(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera->ProcessKeyboard(UP, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera->ProcessKeyboard(DOWN, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS){
        if(reloadedShaders)
            return;
        sceneManager->activeScene->renderManager->HotReloadShaders();
        reloadedShaders = true;
    }
    else{
        reloadedShaders = false;
    }

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        if(buttonPressed)
            return;
        glfwSetInputMode(window, GLFW_CURSOR, mouseLocked ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        mouseLocked = !mouseLocked;
        firstMouse = true;
        buttonPressed = true;
    }
    else{
        buttonPressed = false;
    }

}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    if(!mouseLocked)
        return;

    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                          const void *userParam) {
    // Handle the debug message (e.g., log it, display it, etc.)
    if (id == 131185 || id == 131204) // Filter out annoying Nvidia message of: Buffer you made will use VRAM because you told us that you want it to allocate VRAM.
        return;

    printf("OpenGL Debug Message (id: %d): %s\n", id, message);
}

void InitializeWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    window = glfwCreateWindow(config::SCR_WIDTH, config::SCR_HEIGHT, "TekEngine", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, config::SCR_WIDTH, config::SCR_HEIGHT);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_STENCIL_TEST);

    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugMessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetScrollCallback(window, scroll_callback);

    stbi_set_flip_vertically_on_load(true);
}

int main() {
    InitializeWindow();

    // build and compile our shader program
    // ------------------------------------
    char path[] = "../Tek/Models/StandardCube/StandardCube.gltf";
    //char path[] = "../Tek/Models/Main.1_Sponza/NewSponza_Main_glTF_002.gltf";
    //char path[] = "../Tek/Models/SPHERES/untitled.gltf";

    std::shared_ptr<Shader> objShader = make_shared<Shader>("Texture.vert", "Texture.frag");
    std::shared_ptr<Material> material = make_shared<Material>(objShader);
    std::shared_ptr<Model> modelObj = make_shared<Model>(path);
    std::shared_ptr<Scene> scene = make_shared<Scene>(camera);
    sceneManager->activeScene = scene;
    std::shared_ptr<GameObject> backPack = std::make_shared<GameObject>();
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(modelObj, material);
    backPack->AddComponent<Renderer>(renderer);
    scene->AddGameObject(backPack);

    std::shared_ptr<GameObject> cube = std::make_shared<GameObject>();
    std::shared_ptr<Renderer> renderer2 = std::make_shared<Renderer>(modelObj, material);
    cube->AddComponent<Renderer>(renderer2);
    scene->AddGameObject(cube);

    cube->GetTransform()->position = glm::vec3(0.0f, 3.5f, 0.0f);
    cube->GetTransform()->scale = glm::vec3(0.5f, 0.5f, 0.5f);
    cube->GetTransform()->rotation.setFromEulerAngles(0.0f, 12.5f, 0.0f);


    backPack->GetTransform()->position = glm::vec3(0.0f, 0.0f, 0.0f);
    backPack->GetTransform()->scale = glm::vec3(1, 1, 1);

#pragma region Lights

/**/
    //std::shared_ptr<Renderer> renderer1 = std::make_shared<Renderer>(&modelObj, &objShader);
    std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
    std::shared_ptr<Light> lightComponent = std::make_shared<Light>(Point, 3, glm::vec3(1.0f, 0.1f, 0.1f));
    scene->AddGameObject(light);
    light->AddComponent<Light>(lightComponent);
    //light->AddComponent<Renderer>(renderer1);
    light->GetTransform()->position = glm::vec3(-2, 3, 1);
    //light->GetTransform()->scale = glm::vec3(0.1f, 0.1f, 0.1f);
    scene->lightManager->AddLight(lightComponent);

    //std::shared_ptr<Renderer> renderer2 = std::make_shared<Renderer>(&modelObj, &objShader);
    std::shared_ptr<GameObject> light2 = std::make_shared<GameObject>();
    std::shared_ptr<Light> lightComponent2 = std::make_shared<Light>(Point, 3, glm::vec3(0.1f, 1.0f, 0.1f));
    scene->AddGameObject(light2);
    light2->AddComponent<Light>(lightComponent2);
    //light2->AddComponent<Renderer>(renderer2);
    light2->GetTransform()->position = glm::vec3(-1, 4, 4);
    scene->lightManager->AddLight(lightComponent2);

//    //std::shared_ptr<Renderer> renderer3 = std::make_shared<Renderer>(&modelObj, &objShader);
//    std::shared_ptr<GameObject> light3 = std::make_shared<GameObject>();
//    std::shared_ptr<Light> lightComponent3 = std::make_shared<Light>(Point, 5, glm::vec3(0.1f, 0.1f, 1.0f));
//    scene->AddGameObject(light3);
//    light3->AddComponent<Light>(lightComponent3);
//    //light3->AddComponent<Renderer>(renderer3);
//    light3->GetTransform()->position = glm::vec3(3, 5, -2);
//    //light3->GetTransform()->rotation.setFromEulerAngles(0, 0, 90);
//    scene->lightManager->AddLight(lightComponent3);

    /**/

    //std::shared_ptr<Renderer> renderer2 = std::make_shared<Renderer>(&modelObj, &objShader);
    std::shared_ptr<GameObject> light4 = std::make_shared<GameObject>();
    std::shared_ptr<Light> lightComponent4 = std::make_shared<Light>(Directional, 3, glm::vec3(0.1f, 0.1f, 0.1f));
    scene->AddGameObject(light4);
    light4->AddComponent<Light>(lightComponent4);
    //light2->AddComponent<Renderer>(renderer2);
    light4->GetTransform()->rotation.setFromEulerAngles(90, 0, 0);
    scene->lightManager->AddLight(lightComponent4);



#pragma endregion

    scene->renderManager->Initialize();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        try {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


        //light->GetTransform()->position = glm::vec3(glm::cos(currentFrame), 4, 0);
        //light2->GetTransform()->position = glm::vec3(-glm::cos(currentFrame), 4, 0);
        //light3->GetTransform()->rotation.setFromEulerAngles(30, currentFrame * 10, 0);
        //light4->GetTransform()->rotation.setFromEulerAngles(90 + std::sin(currentFrame) * 10, 0, 0);
        cube->GetTransform()->rotation.setFromEulerAngles(0.0f, currentFrame*10, 0.0f);
        scene->UpdateScene(deltaTime);
        scene->renderManager->Render();



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        }
            catch(std::exception& e){
                std::cerr << "Caught: " << e.what() << std::endl;
            }
    }



    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
