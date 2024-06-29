//
// Created by LucasvanDam on 11/06/2024.
//

#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP
#include <vector>
#include <memory>
#include "../Components/Renderer.hpp"
#include "../GameObject.hpp"


class RenderManager {
private:
    std::vector<std::shared_ptr<Renderer>> renderers;
    std::vector<unsigned int> depthCubeMaps;
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

public:
    void Render();
    void AddRenderer(std::shared_ptr<Renderer> renderer);
    RenderManager(std::shared_ptr<LightManager> lightManager);
    void Initialize();
};


#endif //RENDERMANAGER_HPP
