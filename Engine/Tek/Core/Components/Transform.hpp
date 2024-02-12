#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Math/Quaternion.hpp"
#include "Component.hpp"

class Transform : public Component{
public:
    glm::vec3 position; // Position (translation)
    Quaternion rotation; // Quaternion for rotation
    glm::vec3 scale;    // Scale factors (x, y, z)

    Transform()
            : position(glm::vec3(0.0f)), rotation(1.0f, 0.0f, 0.0f, 0.0f), scale(glm::vec3(1.0f)) {}

    // Get the transformation matrix
    glm::mat4 GetTransformationMatrix() const {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMatrix = CreateRotationMatrix(rotation); // Custom function
        glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), scale);

        return translationMatrix * rotationMatrix * scalingMatrix;
    }

private:
    // Create the rotation matrix from a quaternion
    static glm::mat4 CreateRotationMatrix(const Quaternion& quat) {
        return glm::mat4_cast(quat);
    }
};


#endif //TRANSFORM_HPP