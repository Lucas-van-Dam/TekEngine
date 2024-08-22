#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;

    setupMesh();
}

void Mesh::Destroy()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

// initializes all the buffer objects/arrays
void Mesh::setupMesh()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &SSBO);
//    glGenFramebuffers(1, &depthMapFBO);
//
//    //Shadow preparation
//    glGenTextures(1, &depthMap);
//    glBindTexture(GL_TEXTURE_2D, depthMap);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
//                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glBindVertexArray(0);
}

// render the mesh
void Mesh::Draw(Material &material, std::vector<LightData> lightData)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    //load textures or flat values
    //diffuse
    if(material.AlbedoTexture == nullptr){
        material.shader->setBool("useAlbedoTexture", false);
        material.shader->setVec4("albedo", material.AlbedoColor);
    }
    else{
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(material.shader->ID, "texture_albedo"), 0);
        glBindTexture(GL_TEXTURE_2D, material.AlbedoTexture->id);
    }
    //normal
    if(material.NormalTexture == nullptr){
        material.shader->setBool("useNormalTexture", false);
    }
    else{
        glActiveTexture(GL_TEXTURE1);
        glUniform1i(glGetUniformLocation(material.shader->ID, "texture_normal"), 1);
        glBindTexture(GL_TEXTURE_2D, material.NormalTexture->id);
    }
    //roughness
    if(material.RoughnessTexture == nullptr){
        material.shader->setBool("useRoughnessTexture", false);
        material.shader->setFloat("roughness", material.Roughness);
    }
    else{
        glActiveTexture(GL_TEXTURE2);
        glUniform1i(glGetUniformLocation(material.shader->ID, "texture_roughness"), 2);
        glBindTexture(GL_TEXTURE_2D, material.RoughnessTexture->id);
    }
    //metallic
    if(material.MetallicTexture == nullptr){
        material.shader->setBool("useMetallicTexture", false);
        material.shader->setFloat("metallic", material.Metallic);
    }
    else{
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, material.MetallicTexture->id);
    }

    if(!lightData.empty()) {
        LightData *lightDataStatic = &lightData.front();

        glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
        int totalSize = sizeof(LightData) * lightData.size();
        glBufferData(GL_SHADER_STORAGE_BUFFER, totalSize, lightDataStatic,
                     GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}