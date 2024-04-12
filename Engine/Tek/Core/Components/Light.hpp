#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include "Component.hpp"

enum LightType{
    Spot = 0,
    Directional = 1,
    Ambient = 2,
    Point = 3
};

class Light : public Component{
public:
    explicit Light(LightType type = Spot, float intensity = 1, glm::vec3 color = glm::vec3(1,1,1), float cutOff = -1, float outerCutOff = -1);

    void Update(float deltaTime) override;
    LightType type;
    float intensity;
    glm::vec3 color;
    float cutOff;
private:

};

#endif //LIGHT_HPP