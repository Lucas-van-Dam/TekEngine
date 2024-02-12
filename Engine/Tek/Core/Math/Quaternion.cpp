//
// Created by LucasvanDam on 06/02/2024.
//

#include "Quaternion.hpp"

glm::vec3 Quaternion::getEulerAngles() const {
    // Extract Euler angles using glm::eulerAngles
    glm::vec3 eulerAngles = glm::eulerAngles(*this);
    return eulerAngles;
}

void Quaternion::setFromEulerAngles(float roll, float pitch, float yaw) {
    // Convert Euler angles to rotation matrix
    glm::mat4 rotationMatrix;
    rotationMatrix = glm::rotate(rotationMatrix, yaw, glm::vec3(0.0f, 0.0f, 1.0f));
    rotationMatrix = glm::rotate(rotationMatrix, pitch, glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, roll, glm::vec3(1.0f, 0.0f, 0.0f));

    // Convert rotation matrix to quaternion
    glm::quat result = glm::quat_cast(rotationMatrix);
    *this = Quaternion(result.w, result.x, result.y, result.z);
}