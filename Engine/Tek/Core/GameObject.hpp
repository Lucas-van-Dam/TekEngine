#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include "Components/Transform.hpp"
#include "memory"
#include "vector"

class GameObject : public std::enable_shared_from_this<GameObject>{
public:
    bool enabled = true;

    GameObject() = default;
    ~GameObject() = default;

    template <typename T>
    T* AddComponent();

    template <typename T>
    T* GetComponent();

    void Update(float deltaTime);

    void AddChild(std::shared_ptr<GameObject>);

    std::shared_ptr<GameObject> GetParent();
    void SetParent(std::shared_ptr<GameObject> newParent);

private:
    std::vector<std::unique_ptr<Component>> components;
    std::vector<std::shared_ptr<GameObject>> children;
    std::shared_ptr<GameObject> parent;

};

#endif //GAMEOBJECT_HPP