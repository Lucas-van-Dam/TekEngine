#pragma once

#include <memory>
#include "Tek/GameHierarchy/GameObject.h"
#include "Tek/EditorCamera.h"
#include "Tek/Rendering/LightManager.h"
#include "Tek/Rendering/RenderManager.h"

namespace TEK {

    class Scene : public std::enable_shared_from_this<Scene> {
    public:
        Scene();
        ~Scene();
        void AddGameObject(std::shared_ptr<GameObject> gameObject);
        void DeleteGameObject(std::shared_ptr<GameObject> gameObject);
        void UpdateScene(float deltaTime);
        void ProcessGameObjectDeletion();
        std::shared_ptr<GameObject> GetGameObject(int index);
        std::shared_ptr<EditorCamera> GetEditorCamera();
        std::shared_ptr<EditorCamera> camera;
        std::shared_ptr<LightManager> lightManager;
        std::unique_ptr<RenderManager> renderManager;

    private:
        std::vector<std::shared_ptr<GameObject>> gameObjects;
        std::vector<std::weak_ptr<GameObject>> gameObjectsToDelete;
    };

}

