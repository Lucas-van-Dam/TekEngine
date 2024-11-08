#include "tekpch.h"
#include "Texture.h"

namespace TEK {

    void Texture::Load(const std::string& filePath, std::any metadata)
	{
        std::string typeName;
        if (metadata.has_value()) {
            typeName = std::any_cast<std::string>(metadata);
        }
        else {
            TEK_CORE_ERROR("No type name given at loading of texture: {0}", filePath);
        }

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
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

            id = textureID;
            type = typeName;
        }
        else {
            std::cout << "Texture failed to load at path: " << filePath << std::endl;
            stbi_image_free(data);
        }
	}

	void Texture::Unload()
	{
        if (id) {
            glDeleteTextures(1, &id);
            id = 0;
        }
	}

}