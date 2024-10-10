#include "tekpch.h"
#include "Scene.h"

namespace TEK {

    void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject) {
        gameObjects.push_back(gameObject);
        gameObject->SetScene(shared_from_this());
    }

    void Scene::DeleteGameObject(std::shared_ptr<GameObject> gameObject)
    {
        gameObjectsToDelete.push_back(gameObject);
    }

    void Scene::UpdateScene(float deltaTime) {
        for (const auto& gameObject : gameObjects) {
            gameObject->Update(deltaTime);
        }
    }

    void Scene::ProcessGameObjectDeletion() {
        for (const auto& gameObject : gameObjectsToDelete) {
            auto obj = gameObject.lock();
            if (obj) {
                obj->OnGameObjectDeleted();
                gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
            }
        }
        gameObjectsToDelete.clear();
    }


    std::shared_ptr<EditorCamera> Scene::GetEditorCamera() {
        return camera;
    }

    Scene::Scene() {
        this->camera = EditorCamera::GetInstance();
        lightManager = std::make_unique<LightManager>(5);
        renderManager = std::make_unique<RenderManager>(lightManager, camera);
    }

    Scene::~Scene() {
        gameObjects.clear();
    }

    std::shared_ptr<GameObject> Scene::GetGameObject(int index)
    {
        if (index >= 0 && index < static_cast<int>(gameObjects.size())) {
            auto gameObject = gameObjects[index];
            if (gameObject) {
                return gameObject;
            }
        }
        // Return nullptr if the index is out of bounds or the GameObject is deleted
        return nullptr;
    }

}