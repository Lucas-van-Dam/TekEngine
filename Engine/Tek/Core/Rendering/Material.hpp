#ifndef MATERIAL_HPP
#define MATERIAL_HPP


#include <memory>
#include "Shader.hpp"
#include "Rendering.hpp"

class Material {
private:

public:
    std::shared_ptr<Texture> AlbedoTexture;
    glm::vec4 AlbedoColor;
    std::shared_ptr<Texture> MetallicTexture;
    float Metallic;
    std::shared_ptr<Texture> RoughnessTexture;
    float Roughness;
    std::shared_ptr<Texture> NormalTexture;
    std::shared_ptr<Shader> shader;
    Material(std::shared_ptr<Shader> shader);
    Material();
};


#endif //MATERIAL_HPP
