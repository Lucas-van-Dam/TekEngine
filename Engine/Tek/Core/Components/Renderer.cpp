#include "Renderer.hpp"

#include <utility>
#include "Transform.hpp"
#include "../Scene.hpp"

void Renderer::Draw(glm::mat4 mainLightView, glm::mat4 mainLightProj, int skyboxId, int irradianceMapId, int prefilterMapId, int brdfLUTTextureId, std::vector<int> depthCubeId, int shadowMapId,
                    const shared_ptr<Shader>& overrideShader) {
    auto data = SetLightingBuffer(mainLightView, mainLightProj);
    if(overrideShader != nullptr){
        overrideShader->use();
        overrideShader->setMat4("model", modelMatrix);
        overrideShader->setMat4("view", viewMatrix);
        overrideShader->setMat4("projection", projectionMatrix);
        Material overrideMaterial(overrideShader);
        mesh->Draw(overrideMaterial, data);
        return;
    }
    material->shader->setMat4("model", modelMatrix);
    material->shader->setMat4("view", viewMatrix);
    material->shader->setMat4("projection", projectionMatrix);
    material->shader->setFloat("far_plane", 100.0f);
    glActiveTexture(GL_TEXTURE4);
    glUniform1i(glGetUniformLocation(material->shader->ID, "shadowMap"), 4);
    glBindTexture(GL_TEXTURE_2D, shadowMapId);

    if(skyboxId >= 0){
        glActiveTexture(GL_TEXTURE5);
        glUniform1i(glGetUniformLocation(material->shader->ID, "skyboxCube"), 5);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxId);

        glActiveTexture(GL_TEXTURE6);
        glUniform1i(glGetUniformLocation(material->shader->ID, "irradianceMap"), 6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMapId);

        glActiveTexture(GL_TEXTURE7);
        glUniform1i(glGetUniformLocation(material->shader->ID, "preFilterMap"), 7);
        glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMapId);

        glActiveTexture(GL_TEXTURE8);
        glUniform1i(glGetUniformLocation(material->shader->ID, "brdfLUT"), 8);
        glBindTexture(GL_TEXTURE_2D,brdfLUTTextureId);
    }

    for (int i = 0; i < depthCubeId.size(); i++) {
        glBindTextureUnit(9 + i, depthCubeId[i]);
    }

    mesh->Draw(*material, data);
}

void Renderer::Update(float deltaTime) {
    if(transform == nullptr){
        transform = gameObject->GetTransform();
    }
    modelMatrix = transform->GetWorldTransform();
    viewMatrix = gameObject->GetScene()->GetEditorCamera()->GetViewMatrix();
    projectionMatrix = gameObject->GetScene()->GetEditorCamera()->GetProjectionMatrix();
}

Renderer::Renderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material): mesh(std::move(mesh)), material(std::move(material))
{

}

std::vector<LightData> Renderer::SetLightingBuffer(glm::mat4 mainLightView, glm::mat4 mainLightProj) {
    int amountOfLights = gameObject->GetScene()->lightManager->lights.size();
    int pointIndex = 0;
    std::vector<LightData> lights;
    for (int i = 0; i < amountOfLights; ++i) {
        unsigned int depthCube = -1;
        Light* light = gameObject->GetScene()->lightManager->lights[i].get();

        LightData data(light->intensity,light->color, light->gameObject->GetTransform()->localPosition,
                       light->gameObject->GetTransform()->GetForwardVector(), light->innerCutOff, light->outerCutOff, light->type, mainLightProj, mainLightView);
        lights.emplace_back(data);
    }
    return lights;
}

void Renderer::OnGameObjectAddedToScene() {
    gameObject->GetScene()->renderManager->AddRenderer(shared_from_this());
}
