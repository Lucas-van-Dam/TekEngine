#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include <memory>

class GameObject;

class Component {
public:
    virtual ~Component() = default;
    virtual void Update(float deltaTime) = 0;
    //virtual void Initialize() = 0;
    std::shared_ptr<GameObject> gameObject;
};


#endif //COMPONENT_HPP
