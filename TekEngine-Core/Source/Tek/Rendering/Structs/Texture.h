#pragma once

#include "Tek/AssetManagement/Asset.h"

#include "stb_image_wrapper.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace TEK {
    class Texture : public Asset {
    public:
        Texture() : id(0) {}
        ~Texture() override { Unload(); }
        unsigned int id;

        // Inherited via Asset
        virtual void Load(const std::string& filePath, std::any metadata = {}) override;

        void Unload() override;
    };
}