#pragma once

#include <memory>

#include "Tek/Rendering/Shader.h"
#include "Tek/Rendering/Mesh.h"
#include "Tek/Rendering/Material.h"
#include "Tek/Rendering/Structs/LightData.h"
#include "Tek/GameHierarchy/Components/Component.h"
#include "glm/glm.hpp"

class Transform;
class GameObject;

namespace TEK {

    class Renderer : public Component, public std::enable_shared_from_this<Renderer> {
    public:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;

        Renderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
        ~Renderer();
        void Draw(glm::mat4 mainLightView, glm::mat4 mainLightProj, int skyboxId, int irradianceMapId, int prefilterMapId, int brdfLUTTextureId, std::vector<int> depthCubeId = std::vector<int>(), int shadowMapId = 0, const std::shared_ptr<Shader>&overrideShader = nullptr);

        void Update(float deltaTime) override;

        void OnGameObjectAddedToScene() override;

    private:
        std::vector<LightData> SetLightingBuffer(glm::mat4 mainLightView, glm::mat4 mainLightProj);
        glm::mat4 modelMatrix{};
        glm::mat4 viewMatrix{};
        glm::mat4 projectionMatrix{};

        std::shared_ptr<Transform> transform = nullptr;
    };

}

