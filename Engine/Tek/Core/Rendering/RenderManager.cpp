//
// Created by LucasvanDam on 11/06/2024.
//

#include <glm/ext/matrix_clip_space.hpp>
#include <utility>
#include "RenderManager.hpp"

void RenderManager::Render() {
    ShadowGen();
    RenderOpaques();
    RenderTransparents();
    RenderPostProcessing();
}

void RenderManager::AddRenderer(std::shared_ptr<Renderer> renderer) {
    renderers.push_back(renderer);
}

void RenderManager::RenderOpaques() {
    for(const auto& renderer : renderers){
        renderer->Draw(mainLightView, mainLightProj, depthMap);
    }
}

void RenderManager::RenderTransparents() {

}

void RenderManager::RenderPostProcessing() {

}

void RenderManager::ShadowGen() {
    GenerateMainLightShadows();
}

RenderManager::RenderManager(std::shared_ptr<LightManager> lightManager) : lightManager(std::move(lightManager)), simpleDepthShader(
        make_shared<Shader>("simpleDepthShader.vert", "simpleDepthShader.frag")){
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderManager::GenerateMainLightShadows() {
    std::shared_ptr<Light> light = lightManager->mainLight;
    if(light == nullptr){
        printf("No main light found");
        return;
    }
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = -20.0f, far_plane = 100;
    mainLightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);

    mainLightView = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), (light->gameObject->GetTransform()->rotation * glm::vec3(0.0f,0.0f,1.0f)), (light->gameObject->GetTransform()->rotation * glm::vec3(0.0f,1.0f,0.0f)));
    lightSpaceMatrix = mainLightProj * mainLightView;



    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    simpleDepthShader->use();
    simpleDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    glDisable( GL_CULL_FACE );
    for(const auto& renderer : renderers){
        renderer->Draw(mainLightView, mainLightProj, 0, simpleDepthShader);
    }
    glEnable( GL_CULL_FACE );
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, config::SCR_WIDTH, config::SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
