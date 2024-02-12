#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/quaternion.hpp"

class Quaternion : public glm::quat{
public:
    Quaternion() : glm::quat(){}
    Quaternion(float w, float x, float y, float z) : glm::quat(w,x,y,z) {}
    // Set the quaternion using Euler angles (in radians)
    void setFromEulerAngles(float roll, float pitch, float yaw);

    // Get Euler angles (roll, pitch, yaw) from the quaternion
    glm::vec3 getEulerAngles() const;
};


#endif //QUATERNION_HPP
