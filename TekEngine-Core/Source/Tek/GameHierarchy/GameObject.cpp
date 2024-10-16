#include "tekpch.h"
#include "GameObject.h"

#include "Tek/GameHierarchy/Scene.h"
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
        child->SetScene(scene.lock());
        children.emplace_back(std::move(child));
    }

    std::shared_ptr<GameObject> GameObject::GetParent() {
        if(auto parentPtr = parent.lock())
            return parentPtr;
        //TEK_CORE_ERROR("Object has been deleted but is trying to be accessed");
        return nullptr;
    }

    void GameObject::SetParent(std::shared_ptr<GameObject> newParent) {
        parent = std::move(newParent);
    }

    std::shared_ptr<Transform> GameObject::GetTransform() {
        return transform;
    }

    std::shared_ptr<Scene> GameObject::GetScene() {
        if(scene.lock())
            return scene.lock();
    }

    void GameObject::SetScene(std::shared_ptr<Scene> newScene) {
        if (scene.lock())
            scene.lock().reset(newScene.get());
        else
            scene = newScene; // Explicitly reset scene
        transform->SetOwner(shared_from_this());
        for (const auto& component : components) {
            component->OnGameObjectAddedToScene();
        }
    }

    void GameObject::OnGameObjectDeleted()
    {
        for (auto component : components) {
            component->OnComponentDetach();
        }
        components.clear();
        for (auto child : children) {
            child->OnGameObjectDeleted();
        }
        children.clear();
        transform.reset();
    }

    GameObject::GameObject() : components() {
        transform = std::make_shared<Transform>();
    }

    GameObject::~GameObject()
    {
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
