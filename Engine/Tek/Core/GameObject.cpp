#include "GameObject.hpp"


template <typename T>
T* GameObject::GetComponent() {
    for (const auto& component : components) {
        if (auto ptr = dynamic_cast<T*>(component.get())) {
            return ptr;
        }
    }
    return nullptr;
}

template <typename T>
T* GameObject::AddComponent() {
    components.emplace_back(std::make_unique<T>());
    return dynamic_cast<T*>(components.back().get());
}

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
