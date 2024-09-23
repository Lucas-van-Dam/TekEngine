#pragma once

#include "stb_image_wrapper.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
namespace TEK {
    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };


    static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false) {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else {
            std::cout << "Texture failed to load at path: " << filename << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    static std::shared_ptr<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName, const std::string& directory) {
        if (mat->GetTextureCount(type) > 0) {
            aiString str;
            mat->GetTexture(type, 0, &str);
            //        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            //        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            //            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
            //                return textures_loaded[j];
            //            }
            //        }
            std::shared_ptr<Texture> texture = std::make_shared<Texture>();
            texture->id = TextureFromFile(str.C_Str(), directory);
            texture->type = typeName;
            texture->path = str.C_Str();
            //        textures_loaded.push_back(
            //                texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
            return texture;
        }
        return nullptr;
    }
}