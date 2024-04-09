#include "Scene.hpp"

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObject->SetScene(shared_from_this());
    gameObjects.push_back(gameObject);
}

void Scene::UpdateScene(float deltaTime) {
    for (const auto& gameObject : gameObjects) {
        gameObject->Update(deltaTime);
    }
}

EditorCamera* Scene::GetEditorCamera() {
    return camera.get();
}

Scene::Scene() {
    lightManager = std::make_unique<LightManager>(5);
}
