#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "Components/Transform.hpp"
#include "memory"
#include "vector"

class Scene;

class GameObject : public std::enable_shared_from_this<GameObject>{
public:
    bool enabled = true;

    GameObject();
    ~GameObject() = default;
    GameObject(const GameObject&);

    template <typename T>
    T* AddComponent(std::shared_ptr<T> component) {
        components.emplace_back(component);
        components.back()->gameObject = shared_from_this();
        return dynamic_cast<T*>(components.back().get());
    }

    template <typename T>
    T* GetComponent() {
        for (const auto& component : components) {
            if (auto ptr = dynamic_cast<T*>(component.get())) {
                return ptr;
            }
        }
        return nullptr;
    }


    void Update(float deltaTime);

    void AddChild(std::shared_ptr<GameObject>);

    std::shared_ptr<GameObject> GetParent();

    Transform* GetTransform();

    Scene* GetScene();

    void SetScene(const std::shared_ptr<Scene> &newScene);


private:
    std::vector<std::shared_ptr<Component>> components;
    std::vector<std::shared_ptr<GameObject>> children;
    std::shared_ptr<GameObject> parent;

    std::unique_ptr<Transform> transform;

    std::shared_ptr<Scene> scene;

    void SetParent(std::shared_ptr<GameObject> newParent);

};

#endif //GAMEOBJECT_HPP