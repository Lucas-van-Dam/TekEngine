#ifndef MATERIAL_HPP
#define MATERIAL_HPP


#include <memory>
#include "Shader.hpp"
#include "Rendering.hpp"

class Material {
private:

public:
    Texture AlbedoTexture;
    glm::vec4 AlbedoColor;
    Texture MetallicTexture;
    float Metallic;
    float Roughness;
    Texture NormalTexture;
    std::shared_ptr<Shader> shader;
    Material(std::shared_ptr<Shader> shader);
    Material();
};


#endif //MATERIAL_HPP
