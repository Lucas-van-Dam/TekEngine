#pragma once

#include "Tek/Rendering/Shader.h"
#include "Tek/Rendering/Structs/Texture.h"

namespace TEK {

    class Material {
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
}

