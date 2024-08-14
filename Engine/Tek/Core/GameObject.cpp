#include "GameObject.hpp"
#include "Scene.hpp"

#include <utility>
#include <stdexcept>


void GameObject::Update(float deltaTime) {
    for (const auto& component : components) {
        component->Update(deltaTime);
    }

    for(const auto& child : children){
        child->Update(deltaTime);
    }
}

void GameObject::AddChild(std::shared_ptr<GameObject> child){
    child->SetParent(shared_from_this());
    children.emplace_back(std::move(child));
}

std::shared_ptr<GameObject> GameObject::GetParent() {
    return parent;
}

void GameObject::SetParent(std::shared_ptr<GameObject> newParent) {
    parent = std::move(newParent);
}

Transform* GameObject::GetTransform() {
    return transform.get();
}

Scene *GameObject::GetScene() {
    return scene.get();
}

void GameObject::SetScene(const std::shared_ptr<Scene>& newScene) {
    if (scene) {
        throw std::logic_error("Scene already assigned to GameObject");
    }
    scene.reset(newScene.get()); // Explicitly reset scene
    for(const auto& component : components){
        component->OnGameObjectAddedToScene();
    }
}

GameObject::GameObject() {
    transform = std::make_unique<Transform>();
}

GameObject::GameObject(const GameObject &) {

}
