#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP
#include <vector>
#include <memory>
#include "../Components/Renderer.hpp"
#include "../GameObject.hpp"


class RenderManager {
private:
    std::vector<std::shared_ptr<Renderer>> renderers;
    std::vector<int> depthCubeMaps;
    std::vector<unsigned int> additionalDepthFBOs;
    void RenderOpaques();
    void RenderTransparents();
    void RenderPostProcessing();
    void GenerateShadows();
    void GenerateMainLightShadows();
    void GenerateAdditionalShadows();
    void RenderAll();

    shared_ptr<Shader> DirectionalShadowShader;
    shared_ptr<Shader> AdditionalShadowShader;
    unsigned int depthMapFBO;
    unsigned int depthMap;
    const unsigned int MAIN_SHADOW_WIDTH = 4096, MAIN_SHADOW_HEIGHT = 4096;
    const unsigned int ADDITIONAL_SHADOW_WIDTH = 1024, ADDITIONAL_SHADOW_HEIGHT = 1024;
    std::shared_ptr<LightManager> lightManager;
    glm::mat4 mainLightView;
    glm::mat4 mainLightProj;
    std::vector<std::shared_ptr<Light>> pointLights;

    shared_ptr<Shader> screenShader;
    float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int framebuffer, textureColorbuffer, rbo;
    unsigned int quadVAO, quadVBO;


public:
    void Render();
    void AddRenderer(std::shared_ptr<Renderer> renderer);
    RenderManager(std::shared_ptr<LightManager> lightManager);
    void Initialize();
};


#endif //RENDERMANAGER_HPP
