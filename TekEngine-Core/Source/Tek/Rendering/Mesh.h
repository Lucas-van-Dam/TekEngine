#pragma once

#include "Tek/Rendering/Material.h"
#include "Tek/Rendering/Structs/LightData.h"
#include "Tek/Rendering/Structs/Vertex.h"

namespace TEK {

    class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        unsigned int VAO, SSBO;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void Draw(Material& material, std::vector<LightData> lightData);
        void Destroy();

    private:
        //  render data
        unsigned int VBO, EBO;
        const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
        unsigned int depthMap;

        void setupMesh();
    };
}