#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "../Rendering/Model.hpp"
#include "memory"
#include "vector"
#include "Component.hpp"
#include "glm/glm.hpp"

class Transform;

class Renderer : public Component{
public:
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;

    Renderer(Model *model1, Shader *shader1);
    void Draw();

    void Update(float deltaTime) override;

private:
    std::vector<LightData> SetLightingBuffer();
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    Transform* transform = nullptr;

};


#endif //RENDERER_HPP
