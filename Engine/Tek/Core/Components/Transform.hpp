#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../Math/Quaternion.hpp"
#include "Component.hpp"

class Transform : public Component{
public:
    glm::vec3 localPosition; // Position (translation)
    Quaternion localRotation; // Quaternion for rotation
    glm::vec3 localScale;    // Scale factors (x, y, z)

    Transform()
            : localPosition(glm::vec3(0.0f)), localRotation(1.0f, 0.0f, 0.0f, 0.0f), localScale(glm::vec3(1.0f)) {}

    // Get the transformation matrix
    glm::mat4 GetTransformationMatrix() const;

    glm::mat4 GetWorldTransform() const;

    glm::vec3 GetForwardVector() const;

    glm::vec3 GetWorldPosition() const;
    Quaternion GetWorldRotation() const;
    glm::vec3 GetWorldScale() const;

    void Update(float deltaTime) override;


private:
    // Create the rotation matrix from a quaternion
    static glm::mat4 CreateRotationMatrix(const Quaternion& quat) {
        return glm::mat4_cast(quat);
    }


};


#endif //TRANSFORM_HPP