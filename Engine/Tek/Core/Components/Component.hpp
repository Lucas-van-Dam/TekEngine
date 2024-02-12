#ifndef COMPONENT_HPP
#define COMPONENT_HPP


class Component {
public:
    virtual ~Component() = default;
    virtual void Update(float deltaTime) = 0;
};


#endif //COMPONENT_HPP
