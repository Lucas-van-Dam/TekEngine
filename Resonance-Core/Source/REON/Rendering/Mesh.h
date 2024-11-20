#pragma once

#include "REON/Rendering/Material.h"
#include "REON/Rendering/Structs/LightData.h"
#include "REON/Rendering/Structs/Vertex.h"

namespace REON {

    class Mesh {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void Draw(Material& material, std::vector<LightData> lightData) const;
        void Destroy();

    private:
        void setupMesh();

    private:
        //  render data
        unsigned int m_VBO, m_EBO;
        unsigned int m_DepthMap;
        // mesh data
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;
        unsigned int m_VAO, m_SSBO;

    };
}