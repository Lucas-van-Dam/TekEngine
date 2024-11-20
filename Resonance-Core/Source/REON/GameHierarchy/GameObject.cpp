#include "reonpch.h"
#include "GameObject.h"

#include "REON/GameHierarchy/Scene.h"
#include "REON/GameHierarchy/Components/Transform.h"


namespace REON {

    void GameObject::Update(float deltaTime) {
        for (const auto& component : m_Components) {
            component->Update(deltaTime);
        }

        for (const auto& child : m_Children) {
            child->Update(deltaTime);
        }
        
    }

    void GameObject::AddChild(std::shared_ptr<GameObject> child) {
        child->SetParent(shared_from_this());
        child->SetScene(m_Scene.lock());
        m_Children.emplace_back(std::move(child));
    }

    std::shared_ptr<GameObject> GameObject::GetParent() {
        if(auto parentPtr = m_Parent.lock())
            return parentPtr;
        //REON_CORE_ERROR("Object has been deleted but is trying to be accessed");
        return nullptr;
    }

    void GameObject::SetParent(std::shared_ptr<GameObject> newParent) {
        m_Parent = std::move(newParent);
    }

    std::shared_ptr<Transform> GameObject::GetTransform() {
        return m_Transform;
    }

    std::shared_ptr<Scene> GameObject::GetScene() {
        if(m_Scene.lock())
            return m_Scene.lock();
    }

    void GameObject::SetScene(std::shared_ptr<Scene> newScene) {
        if (m_Scene.lock())
            m_Scene.lock().reset(newScene.get());
        else
            m_Scene = newScene; // Explicitly reset scene
        m_Transform->SetOwner(shared_from_this());
        for (const auto& component : m_Components) {
            component->OnGameObjectAddedToScene();
        }
    }

    void GameObject::OnGameObjectDeleted()
    {
        for (auto component : m_Components) {
            component->OnComponentDetach();
        }
        m_Components.clear();
        for (auto child : m_Children) {
            child->OnGameObjectDeleted();
        }
        m_Children.clear();
        m_Transform.reset();
    }

    GameObject::GameObject() : m_Components() {
        m_Transform = std::make_shared<Transform>();
    }

    GameObject::~GameObject()
    {
    }

    GameObject::GameObject(const GameObject&) {

    }

    void GameObject::SetName(std::string newName) {
        this->m_Name = std::move(newName);
    }

    std::string GameObject::GetName() {
        return m_Name;
    }



}
