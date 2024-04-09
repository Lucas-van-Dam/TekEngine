#ifndef RENDERING_HPP
#define RENDERING_HPP

#include "glm/glm.hpp"
#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};
struct Texture {
    unsigned int id;
    string type;
    string path;
};
struct LightData{
    LightData(float intensity, glm::vec3 lightColor, glm::vec3 position = glm::vec3(std::numeric_limits<float>::max()), glm::vec3 direction = glm::vec3(),
              float innerCutOff = -1, float outerCutOff = -1)
        : position(position.x, position.y, position.x, innerCutOff), direction(direction.x, direction.y, direction.z, outerCutOff), lightColor(lightColor.x, lightColor.y, lightColor.z, intensity){
    }
    glm::vec4 position;
    glm::vec4 direction;
    glm::vec4 lightColor;
};

#endif //RENDERING_HPP
