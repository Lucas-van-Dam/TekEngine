//
// Created by LucasvanDam on 11/06/2024.
//

#include <glm/ext/matrix_clip_space.hpp>
#include <utility>
#include "RenderManager.hpp"

void RenderManager::Render() {
    GenerateShadows();
    RenderOpaques();
    RenderTransparents();
    RenderPostProcessing();
}

void RenderManager::AddRenderer(std::shared_ptr<Renderer> renderer) {
    renderers.push_back(renderer);
}

void RenderManager::RenderOpaques() {
    for(const auto& renderer : renderers){
        renderer->Draw(mainLightView, mainLightProj, depthCubeMaps, depthMap);
    }
}

void RenderManager::RenderTransparents() {

}

void RenderManager::RenderPostProcessing() {

}

void RenderManager::GenerateShadows() {
    GenerateMainLightShadows();
    GenerateAdditionalShadows();
}

RenderManager::RenderManager(std::shared_ptr<LightManager> lightManager) : lightManager(std::move(lightManager)), DirectionalShadowShader(
        make_shared<Shader>("DirectionalShadow.vert", "DirectionalShadow.frag")),
        AdditionalShadowShader(make_shared<Shader>("OmnidirectionalShadow.vert", "OmnidirectionalShadow.frag", "OmnidirectionalShadow.geom")){
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 MAIN_SHADOW_WIDTH, MAIN_SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
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
        printf("No main light found\n");
        return;
    }
    glm::mat4 lightProjection, lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane = -20.0f, far_plane = 100;
    mainLightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);

    mainLightView = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), (light->gameObject->GetTransform()->rotation * glm::vec3(0.0f,0.0f,1.0f)), (light->gameObject->GetTransform()->rotation * glm::vec3(0.0f,1.0f,0.0f)));
    lightSpaceMatrix = mainLightProj * mainLightView;



    glViewport(0, 0, MAIN_SHADOW_WIDTH, MAIN_SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    DirectionalShadowShader->use();
    DirectionalShadowShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);
    glDisable( GL_CULL_FACE );
    for(const auto& renderer : renderers){
        renderer->Draw(mainLightView, mainLightProj, std::vector<int>(), 0, DirectionalShadowShader);
    }
    glEnable( GL_CULL_FACE );
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, config::SCR_WIDTH, config::SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderManager::GenerateAdditionalShadows() {
    for (int i = 0; i < pointLights.size(); ++i){
        std::shared_ptr<Light> light = pointLights[i];
        glm::vec3 lightPos = light->gameObject->GetTransform()->position;
        float near_plane = 1.0f;
        float far_plane  = 100.0f;
        glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)ADDITIONAL_SHADOW_WIDTH / (float)ADDITIONAL_SHADOW_HEIGHT, near_plane, far_plane);
        std::vector<glm::mat4> shadowTransforms;
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        glViewport(0, 0, ADDITIONAL_SHADOW_WIDTH, ADDITIONAL_SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, additionalDepthFBOs[i]);
        glClear(GL_DEPTH_BUFFER_BIT);
        AdditionalShadowShader->use();
        for (unsigned int j = 0; j < 6; ++j)
            AdditionalShadowShader->setMat4("shadowMatrices[" + std::to_string(j) + "]", shadowTransforms[j]);
        AdditionalShadowShader->setFloat("far_plane", far_plane);
        AdditionalShadowShader->setVec3("lightPos", lightPos);
        for(const auto& renderer : renderers){
            renderer->Draw(glm::mat4(), glm::mat4(), std::vector<int>(), 0, AdditionalShadowShader);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, config::SCR_WIDTH, config::SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void RenderManager::Initialize() {
    for(const std::shared_ptr<Light>& light : lightManager->lights){
        if(light->type == Point){
            pointLights.emplace_back(light);
            unsigned int depthCubemap, depthFBO;
            glGenFramebuffers(1, &depthFBO);
            glGenTextures(1, &depthCubemap);
            glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
            for (unsigned int i = 0; i < 6; ++i)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, ADDITIONAL_SHADOW_WIDTH, ADDITIONAL_SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            // attach depth texture as FBO's depth buffer
            glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
            glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            additionalDepthFBOs.emplace_back(depthFBO);
            depthCubeMaps.emplace_back(depthCubemap);
        }
    }
}


