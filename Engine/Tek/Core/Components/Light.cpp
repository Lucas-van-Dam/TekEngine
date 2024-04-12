#include "Light.hpp"

Light::Light(LightType type, float intensity, glm::vec3 color, float cutOff, float outerCutOff)
    : type(type), intensity(intensity), color(color), cutOff(cutOff)
{

}

void Light::Update(float deltaTime) {

}
