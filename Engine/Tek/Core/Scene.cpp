#include "Scene.hpp"

void Scene::AddGameObject(std::unique_ptr<GameObject> gameObject) {
    gameObjects.push_back(std::move(gameObject));
}

void Scene::UpdateScene(float deltaTime) {
    for (const auto& gameObject : gameObjects) {
        gameObject->Update(deltaTime);
    }
}