#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace REON {

    class Shader {
    public:
        // constructor reads and builds the shader
        Shader(const std::string& vertexFileName, const std::string& fragmentFileName, const std::string& geometryFileName = "");
        // use/activate the shader
        void use() const;
        // utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w) const;
        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;

        void ReloadShader();

    public:
        // the program ID
        unsigned int ID;

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
        static void checkCompileErrors(unsigned int shader, const std::string& type);

    private:
        std::string m_VertexPath, m_FragmentPath, m_GeometryPath;
        GLuint m_FragmentID, m_VertexID, m_GeometryID;
    };
}