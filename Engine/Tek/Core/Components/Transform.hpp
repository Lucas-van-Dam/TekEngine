#ifndef TEKENGINE_TRANSFORM_HPP
#define TEKENGINE_TRANSFORM_HPP

#include "glm/glm.hpp"

class Transform {
public:
    glm::vec3 getPosition();
    void setPosition(glm::vec3 newPosition);
    glm::vec3 getScale();
    void setScale(glm::vec3 newScale);
    float getRotation();
    void Rotate(float);
private:
    glm::mat4 matrix;
};


#endif //TEKENGINE_TRANSFORM_HPP
