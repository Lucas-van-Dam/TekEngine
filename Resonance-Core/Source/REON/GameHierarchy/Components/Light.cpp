#include "reonpch.h"
#include "Light.h"

namespace REON {

    Light::Light(LightType type, float intensity, glm::vec3 color, float innerCutOff, float outerCutOff)
        : type(type), intensity(intensity), color(color), innerCutOff(innerCutOff), outerCutOff(outerCutOff)
    {

    }

    void Light::Update(float deltaTime) {

    }

    void Light::OnGameObjectAddedToScene()
    {
    }

    void Light::OnComponentDetach()
    {
    }

}