#include "tekpch.h"
#include "GameObject.h"

#include "Tek/GameHierarchy/Scene.h"
#include "Tek/GameHierarchy/Components/Component.h"
#include "Tek/GameHierarchy/Components/Transform.h"


namespace TEK {

    void GameObject::Update(float deltaTime) {
        for (const auto& component : components) {
            component->Update(deltaTime);
        }

        for (const auto& child : children) {
            child->Update(deltaTime);
        }
    }

    void GameObject::AddChild(std::shared_ptr<GameObject> child) {
        child->SetParent(shared_from_this());
        child->SetScene(scene);
        children.emplace_back(std::move(child));
    }

    std::shared_ptr<GameObject> GameObject::GetParent() {
        return parent;
    }

    void GameObject::SetParent(std::shared_ptr<GameObject> newParent) {
        parent = std::move(newParent);
    }

    std::shared_ptr<Transform> GameObject::GetTransform() {
        return transform;
    }

    std::shared_ptr<Scene> GameObject::GetScene() {
        return scene;
    }

    void GameObject::SetScene(const std::shared_ptr<Scene>& newScene) {
        scene.reset(newScene.get()); // Explicitly reset scene
        transform->gameObject = shared_from_this();
        for (const auto& component : components) {
            component->OnGameObjectAddedToScene();
        }
    }

    GameObject::GameObject() : components() {
        transform = std::make_shared<Transform>();
    }

    GameObject::GameObject(const GameObject&) {

    }

    void GameObject::SetName(std::string newName) {
        this->name = std::move(newName);
    }

    std::string GameObject::GetName() {
        return name;
    }

}
