#include "Scene.hpp"

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObjects.push_back(gameObject);
    gameObject->SetScene(shared_from_this());
}

void Scene::UpdateScene(float deltaTime) {
    for (const auto& gameObject : gameObjects) {
        gameObject->Update(deltaTime);
    }
}

EditorCamera* Scene::GetEditorCamera() {
    return camera.get();
}

Scene::Scene(const shared_ptr<EditorCamera>& camera) {
    this->camera = camera;
    lightManager = std::make_unique<LightManager>(5);
    renderManager = std::make_unique<RenderManager>(lightManager, camera);
}

void Scene::PrintSceneHierarchy() {
    cout << gameObjects.size() << std::endl;
}
