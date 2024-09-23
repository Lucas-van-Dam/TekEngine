#pragma once

#include "glm/glm.hpp"

struct LightData {
    LightData(float intensity, glm::vec3 lightColor, glm::vec3 position, glm::vec3 direction,
        float innerCutOff, float outerCutOff, int type, glm::mat4 projection, glm::mat4 view)
        : position(position.x, position.y, position.z, type), direction(direction.x, direction.y, direction.z, glm::radians(innerCutOff)), lightColor(lightColor.x, lightColor.y, lightColor.z, intensity),
        projection(projection), view(view)
    {

    }
    glm::vec4 position;
    glm::vec4 direction;
    glm::vec4 lightColor;
    glm::mat4 projection;
    glm::mat4 view;
};