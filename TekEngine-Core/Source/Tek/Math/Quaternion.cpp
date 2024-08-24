#include "tekpch.h"
#include "Quaternion.h"

namespace TEK {

    glm::vec3 Quaternion::getEulerAngles() const {
        // Extract Euler angles using glm::eulerAngles
        glm::vec3 angles;

        // roll (x-axis rotation)
        double sinr_cosp = 2 * (this->w * this->x + this->y * this->z);
        double cosr_cosp = 1 - 2 * (this->x * this->x + this->y * this->y);
        angles.x = std::atan2(sinr_cosp, cosr_cosp);

        // pitch (y-axis rotation)
        double sinp = std::sqrt(1 + 2 * (this->w * this->y - this->x * this->z));
        double cosp = std::sqrt(1 - 2 * (this->w * this->y - this->x * this->z));
        angles.y = 2 * std::atan2(sinp, cosp) - std::numbers::pi / 2;

        // yaw (z-axis rotation)
        double siny_cosp = 2 * (this->w * this->z + this->x * this->y);
        double cosy_cosp = 1 - 2 * (this->y * this->y + this->z * this->z);
        angles.z = std::atan2(siny_cosp, cosy_cosp);

        return glm::degrees(angles);
    }

    // roll, pitch and yaw in degrees
    void Quaternion::setFromEulerAngles(float roll, float pitch, float yaw) {
        roll = glm::radians(roll);
        pitch = glm::radians(pitch);
        yaw = glm::radians(yaw);
        double cr = cos(roll * 0.5);
        double sr = sin(roll * 0.5);
        double cp = cos(pitch * 0.5);
        double sp = sin(pitch * 0.5);
        double cy = cos(yaw * 0.5);
        double sy = sin(yaw * 0.5);

        this->w = cr * cp * cy + sr * sp * sy;
        this->x = sr * cp * cy - cr * sp * sy;
        this->y = cr * sp * cy + sr * cp * sy;
        this->z = cr * cp * sy - sr * sp * cy;
    }

}