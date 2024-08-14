#ifndef MESH_HPP
#define MESH_HPP

#include "glm/glm.hpp"
#include "Shader.hpp"
#include <string>
#include <vector>
#include "Rendering.hpp"
#include "Material.hpp"

using namespace std;

class Mesh {
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    std::shared_ptr<Material> material;
    unsigned int VAO, SSBO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, std::shared_ptr<Material> material);

    void Draw(Shader &shader, std::vector<LightData> lightData);
    void Destroy();

private:
    //  render data
    unsigned int VBO, EBO;
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMap;

    void setupMesh();
};

#endif //MESH_HPP
