#pragma once

#include <memory>

#include "REON/Rendering/Shader.h"
#include "REON/Rendering/Mesh.h"
#include "REON/Rendering/Material.h"
#include "REON/Rendering/Structs/LightData.h"
#include "REON/GameHierarchy/Components/Component.h"
#include "glm/glm.hpp"



namespace REON {

    class Transform;
    class GameObject;

    class Renderer : public Component, public std::enable_shared_from_this<Renderer> {
    public:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Material> material;

        Renderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
        ~Renderer();
        void Draw(glm::mat4 mainLightView, glm::mat4 mainLightProj, int skyboxId, int irradianceMapId, int prefilterMapId, int brdfLUTTextureId, std::vector<int> depthCubeId = std::vector<int>(), int shadowMapId = 0, const std::shared_ptr<Shader>&overrideShader = nullptr);

        void Update(float deltaTime) override;

        void SetOwner(std::shared_ptr<GameObject> owner) override;

        void OnGameObjectAddedToScene() override;
        void OnComponentDetach() override;

    private:
        std::vector<LightData> SetLightingBuffer(glm::mat4 mainLightView, glm::mat4 mainLightProj);
        glm::mat4 modelMatrix{};
        glm::mat4 viewMatrix{};
        glm::mat4 projectionMatrix{};

        std::shared_ptr<Transform> transform = nullptr;
    };

}

