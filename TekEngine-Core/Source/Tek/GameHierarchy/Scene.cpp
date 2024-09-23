#include "tekpch.h"
#include "Scene.h"

namespace TEK {

    void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject) {
        gameObjects.push_back(gameObject);
        gameObject->SetScene(shared_from_this());
    }

    void Scene::UpdateScene(float deltaTime) {
        for (const auto& gameObject : gameObjects) {
            gameObject->Update(deltaTime);
        }
    }

    std::shared_ptr<EditorCamera> Scene::GetEditorCamera() {
        return camera;
    }

    Scene::Scene() {
        this->camera = EditorCamera::GetInstance();
        lightManager = std::make_unique<LightManager>(5);
        renderManager = std::make_unique<RenderManager>(lightManager, camera);
    }

    void Scene::PrintSceneHierarchy() {
        std::cout << gameObjects.size() << std::endl;
    }

}