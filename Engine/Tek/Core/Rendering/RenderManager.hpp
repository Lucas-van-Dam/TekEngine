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
    void RenderOpaques();
    void RenderTransparents();
    void RenderPostProcessing();
    void ShadowGen();
    void GenerateMainLightShadows();

    shared_ptr<Shader> simpleDepthShader;
    unsigned int depthMapFBO;
    unsigned int depthMap;
    const unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
    std::shared_ptr<LightManager> lightManager;
    glm::mat4 mainLightView;
    glm::mat4 mainLightProj;

public:
    void Render();
    void AddRenderer(std::shared_ptr<Renderer> renderer);
    RenderManager(std::shared_ptr<LightManager> lightManager);
};


#endif //RENDERMANAGER_HPP
