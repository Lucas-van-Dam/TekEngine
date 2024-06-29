#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "../Rendering/Model.hpp"
#include "memory"
#include "vector"
#include "Component.hpp"
#include "glm/glm.hpp"

class Transform;

class Renderer : public Component, public std::enable_shared_from_this<Renderer>{
public:
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;

    Renderer(Model *model1, Shader *shader1);
    void Draw(glm::mat4 mainLightView, glm::mat4 mainLightProj, std::vector<int> depthCubeId = std::vector<int>(),int shadowMapId = 0,const shared_ptr<Shader>& overrideShader = nullptr);

    void Update(float deltaTime) override;

    void OnGameobjectAddedToScene() override;

private:
    std::vector<LightData> SetLightingBuffer(glm::mat4 mainLightView, glm::mat4 mainLightProj);
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    Transform* transform = nullptr;

};


#endif //RENDERER_HPP
