#include "tekpch.h"
#include "Transform.h"

#include "glm/glm.hpp"
#include "Tek/GameHierarchy/GameObject.h"

namespace TEK {

    void Transform::Update(float deltaTime) {

    }

    glm::mat4 Transform::GetTransformationMatrix() const {
        glm::mat4 transformationMatrix = CreateRotationMatrix(localRotation);
        transformationMatrix = glm::scale(transformationMatrix, localScale);
        transformationMatrix = glm::translate(transformationMatrix, localPosition);

        return transformationMatrix;
    }

    glm::mat4 Transform::GetWorldTransform() const {
        glm::vec3 worldScale = GetWorldScale();
        Quaternion worldRotation = GetWorldRotation();
        glm::vec3 worldPosition = GetWorldPosition();

        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), worldScale);
        glm::mat4 rotationMatrix = glm::mat4_cast(worldRotation);
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), worldPosition);

        return translationMatrix * rotationMatrix * scaleMatrix;
    }

    glm::vec3 Transform::GetForwardVector() const {
        // Assuming your rotation quaternion is normalized
        glm::vec3 forward = glm::mat3_cast(glm::normalize(localRotation)) * glm::vec3(0.0f, 0.0f, 1.0f);
        return glm::normalize(forward);
    }

    glm::vec3 Transform::GetWorldPosition() const {
        glm::vec3 worldPosition = localPosition;

        std::shared_ptr<GameObject> parent = gameObject->GetParent();
        while (parent != nullptr) {
            worldPosition += parent->GetTransform()->localPosition;
            parent = parent->GetParent();
        }

        return worldPosition;
    }

    Quaternion Transform::GetWorldRotation() const {
        Quaternion worldRotation = localRotation;

        std::shared_ptr<GameObject> parent = gameObject->GetParent();
        while (parent != nullptr) {
            worldRotation *= parent->GetTransform()->localRotation;
            parent = parent->GetParent();
        }

        return worldRotation;
    }

    glm::vec3 Transform::GetWorldScale() const {
        glm::vec3 worldScale = localScale;

        std::shared_ptr<GameObject> parent = gameObject->GetParent();
        while (parent != nullptr) {
            worldScale *= parent->GetTransform()->localScale;
            parent = parent->GetParent();
        }

        return worldScale;
    }

}