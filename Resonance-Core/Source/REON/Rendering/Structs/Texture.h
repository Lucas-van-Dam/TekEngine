#pragma once

#include "REON/AssetManagement/Asset.h"

#include "stb_image_wrapper.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace REON {
    class Texture : public Asset {
    public:
        Texture() : m_Id(0) {}
        ~Texture() override { Unload(); }

        // Inherited via Asset
        virtual void Load(const std::string& filePath, std::any metadata = {}) override;

        void Unload() override;

        unsigned int GetId();

    private:
        unsigned int m_Id;
    };
}