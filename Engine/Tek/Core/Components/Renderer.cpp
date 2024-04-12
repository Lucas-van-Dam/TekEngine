#include "Renderer.hpp"
#include "Transform.hpp"
#include "../GameObject.hpp"
#include "../Scene.hpp"

void Renderer::Draw() {
    shader->use();
    shader->setMat4("model", modelMatrix);
    shader->setMat4("view", viewMatrix);
    shader->setMat4("projection", projectionMatrix);
    auto data = SetLightingBuffer();
    model->Draw(*shader, data);
}

void Renderer::Update(float deltaTime) {
    if(transform == nullptr){
        transform = gameObject->GetTransform();
    }
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform->position);
    modelMatrix = glm::mat4_cast(glm::normalize(transform->rotation)) * modelMatrix;
    modelMatrix = glm::scale(modelMatrix, transform->scale);
    viewMatrix = gameObject->GetScene()->GetEditorCamera()->GetViewMatrix();
    projectionMatrix = gameObject->GetScene()->GetEditorCamera()->GetProjectionMatrix();
    Draw();
}

Renderer::Renderer(Model *model1, Shader *shader1): model(model1), shader(shader1)
{

}

std::vector<LightData> Renderer::SetLightingBuffer() {
    int amountOfLights = gameObject->GetScene()->lightManager->lights.size();
    std::vector<LightData> lights;
    for (int i = 0; i < amountOfLights; ++i) {
        Light* light = gameObject->GetScene()->lightManager->lights[i].get();
        LightData data(light->intensity,light->color, light->gameObject->GetTransform()->position,
                       light->gameObject->GetTransform()->rotation.getEulerAngles(), light->cutOff, light->type);
        lights.emplace_back(data);
    }
    return lights;
}
