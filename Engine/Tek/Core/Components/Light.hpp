#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include "Component.hpp"

enum LightType{
    Point,
    Directional,
    Spot,
    Ambient
};

class Light : public Component{
public:
    explicit Light(LightType type = Spot, float intensity = 1, glm::vec3 color = glm::vec3(1,1,1), float innerCutOff = -1, float outerCutOff = -1);

    void Update(float deltaTime) override;
    LightType type;
    float intensity;
    glm::vec3 color;
    float innerCutOff;
    float outerCutOff;
private:

};

#endif //LIGHT_HPP