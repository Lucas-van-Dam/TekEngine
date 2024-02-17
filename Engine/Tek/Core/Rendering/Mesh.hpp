#ifndef MESH_HPP
#define MESH_HPP

#include "glm/glm.hpp"
#include "../../Shader.hpp"
#include <string>
#include <vector>
#include "Rendering.hpp"

using namespace std;

class Mesh {
public:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Shader &shader);

private:
    //  render data
    unsigned int VBO, EBO;

    void setupMesh();
};

#endif //MESH_HPP
