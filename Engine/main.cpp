#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Tek/Shader.hpp"
#include "TekEngine.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "Tek/External/stb_image.h"
#include "Tek/Core/EditorCamera.hpp"
#include "Tek/Core/Rendering/Model.hpp"
#include "Tek/Core/Scene.hpp"
#include "Tek/Core/Components/Renderer.hpp"
#include "Tek/Core/Audio/AudioManager.hpp"


float deltaTime = 0.0f;    // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

float lastX = config::SCR_WIDTH / 2.0f;
float lastY = config::SCR_HEIGHT / 2.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

std::shared_ptr<EditorCamera> camera = std::make_shared<EditorCamera>(glm::vec3(0.0f, 0.0f, 3.0f));

GLFWwindow *window;


bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
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
    printf("OpenGL Debug Message: %s\n", message);
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

//    AudioManager* audio = new AudioManager;
//
//    audio->Initialize();
//
//    delete audio;

    glViewport(0, 0, 800, 600);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_STENCIL_TEST);

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

unsigned int loadTexture(const char *path);

int main() {
//    // Create an EditorCamera instance
//   // EditorCamera camera1();
//    std::shared_ptr<EditorCamera> camera_shared= std::make_shared<EditorCamera>(glm::vec3(0.0f, 0.0f, 3.0f));
//    // Assign the camera to the scene
//    Scene scene1;
//    //std::shared_ptr<EditorCamera> camera_test(new EditorCamera());
//    scene1.camera = camera_shared;
//
//
//    // Print initial position
//    std::cout << "Position 1: "
//              << scene1.camera->GetPosition().x
//              << ", " << scene1.camera->GetPosition().y
//              << ", " << scene1.camera->GetPosition().z << std::endl;
//
//    // Update the camera position
//    camera_shared->SetPosition(glm::vec3(1, 2, 4));
//
//    // Print updated position
//    std::cout << "Position 2: "
//              << scene1.camera->GetPosition().x
//              << ", " << scene1.camera->GetPosition().y
//              << ", " << scene1.camera->GetPosition().z << std::endl;
//
//    return 0;

    InitializeWindow();

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("TestShader.vert", "TestShader.frag"); // you can name your shader files however you like
    Shader litShader("TestShader.vert", "TestShader.frag");
    Shader lightShader("LightShader.vert", "LightShader.frag");

    char path[] = "C:/Users/LucasvanDam/Documents/TekEngine/Engine/Tek/Models/backpack/backpack.obj";

    Shader objShader("Texture.vert", "Texture.frag");
    Model modelObj(path);
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->camera = camera;
    std::shared_ptr<GameObject> backPack = std::make_shared<GameObject>();
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(&modelObj, &objShader);
    scene->AddGameObject(backPack);
    backPack->AddComponent<Renderer>(renderer);

    backPack->GetTransform()->position = glm::vec3(0.0f, 0.0f, 0.0f);
    backPack->GetTransform()->scale = glm::vec3(2.0f, 2.0f, 2.0f);

    //std::shared_ptr<Renderer> renderer1 = std::make_shared<Renderer>(&modelObj, &objShader);
    std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
    std::shared_ptr<Light> lightComponent = std::make_shared<Light>(Spot, 4, glm::vec3(1.0f, 0.1f, 0.1f));
    scene->AddGameObject(light);
    light->AddComponent<Light>(lightComponent);
    //light->AddComponent<Renderer>(renderer1);
    light->GetTransform()->position = glm::vec3(-1, 1, 4);
    scene->lightManager->AddLight(lightComponent);

    //std::shared_ptr<Renderer> renderer2 = std::make_shared<Renderer>(&modelObj, &objShader);
    std::shared_ptr<GameObject> light2 = std::make_shared<GameObject>();
    std::shared_ptr<Light> lightComponent2 = std::make_shared<Light>(Spot, 5, glm::vec3(0.1f, 1.0f, 0.1f));
    scene->AddGameObject(light2);
    light2->AddComponent<Light>(lightComponent2);
    //light2->AddComponent<Renderer>(renderer2);
    light2->GetTransform()->position = glm::vec3(-1, 1, 4);
    scene->lightManager->AddLight(lightComponent2);


    Shader shader("Transparent.vert", "Transparent.frag");



    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f, 0.2f, 2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f, 2.0f, -12.0f),
            glm::vec3(0.0f, 0.0f, -3.0f)
    };

//    litShader.setInt("material.diffuse", 0);
//    litShader.setInt("material.specular", 1);
    // configure global opengl state
    // -----------------------------

    // build and compile shaders
    // -------------------------


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
            // positions                      // texture Coords    // normals
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
    };
    float planeVertices[] = {
            // positions          // texture Coords               // normals
            5.0f, -0.5f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -5.0f, -0.5f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f,

            5.0f, -0.5f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            -5.0f, -0.5f, -5.0f, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f,
            5.0f, -0.5f, -5.0f, 2.0f, 2.0f, 0.0f, 1.0f, 0.0f
    };
    float transparentVertices[] = {
            // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
            1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

            0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
            1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.5f, 0.0f, 1.0f, 0.0f
    };

    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (5 * sizeof(float)));
    // plane VAO
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (5 * sizeof(float)));
    // transparent VAO
    unsigned int transparentVAO, transparentVBO;
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    unsigned int cubeTexture = loadTexture(
            "C:\\Users\\LucasvanDam\\Documents\\TekEngine\\Engine\\Tek\\Textures\\wall.jpg");
    unsigned int floorTexture = loadTexture(
            "C:\\Users\\LucasvanDam\\Documents\\TekEngine\\Engine\\Tek\\Textures\\container.jpg");
    unsigned int transparentTexture = loadTexture(
            "C:\\Users\\LucasvanDam\\Documents\\TekEngine\\Engine\\Tek\\Textures\\blending_transparent_window.png");

    // transparent vegetation locations
    // --------------------------------
    vector<glm::vec3> vegetation
            {
                    glm::vec3(-1.5f, 0.0f, -0.48f),
                    glm::vec3(1.5f, 0.0f, 0.51f),
                    glm::vec3(0.0f, 0.0f, 0.7f),
                    glm::vec3(-0.3f, 0.0f, -2.3f),
                    glm::vec3(0.5f, 0.0f, -0.6f)
            };

    // shader configuration
    // --------------------
    shader.setInt("texture1", 0);


    double lastTime = glfwGetTime();
    int nbFrames = 0;

    //objShader.LightingShaderGeneration(scene->lightManager.get());

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

//        // Measure speed
//        double currentTime = glfwGetTime();
//        nbFrames++;
//        if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
//            // printf and reset timer
//            printf("%f ms/frame\n", 1000.0 / double(nbFrames));
//            nbFrames = 0;
//            lastTime += 1.0;
//        }

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

//        // draw objects
//        shader.use();
//        glm::mat4 projection = camera->GetProjectionMatrix();
//        glm::mat4 view = camera->GetViewMatrix();
//        glm::mat4 model = glm::mat4(1.0f);
//        shader.setMat4("projection", projection);
//        shader.setMat4("view", view);
//        // cubes
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // floor
//        glBindVertexArray(planeVAO);
//        glBindTexture(GL_TEXTURE_2D, floorTexture);
//        model = glm::mat4(1.0f);
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
////        // vegetation
////        glBindVertexArray(transparentVAO);
////        glBindTexture(GL_TEXTURE_2D, transparentTexture);
////        for (unsigned int i = 0; i < vegetation.size(); i++)
////        {
////            model = glm::mat4(1.0f);
////            model = glm::translate(model, vegetation[i]);
////            shader.setMat4("model", model);
////            glDrawArrays(GL_TRIANGLES, 0, 6);
////        }
        light->GetTransform()->position = glm::vec3(sin(currentFrame) * 3, 3, cos(currentFrame) * 3);
        light2->GetTransform()->position = glm::vec3(-sin(currentFrame) * 3, 3, -cos(currentFrame) * 3);
        scene->UpdateScene(deltaTime);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

unsigned int loadTexture(char const *path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE
                                                                            : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
