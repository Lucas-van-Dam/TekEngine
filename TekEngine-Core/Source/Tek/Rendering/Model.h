#pragma once

#include "assimp/DefaultLogger.hpp"
#include "assimp/Logger.hpp"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "Tek/GameHierarchy/GameObject.h"
#include <glm/glm.hpp>
#include "Tek/Math/Quaternion.h"
#include "Tek/Rendering/Structs/Texture.h"
#include "Tek/Rendering/Mesh.h"

struct aiNode;
struct aiMesh;


namespace TEK {
    class Shader;
    struct LightData;

    class Model {
    public:
        // model data
        std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> meshes;
        std::string directory;

        explicit Model(const char* path, const std::shared_ptr<GameObject>& parent) {
            Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
            Assimp::LogStream* stderrStream = Assimp::LogStream::createDefaultStream(aiDefaultLogStream_STDERR);
            Assimp::DefaultLogger::get()->attachStream(stderrStream, Assimp::Logger::VERBOSE | Assimp::Logger::Debugging |
                Assimp::Logger::VERBOSE);
            loadModel(path, parent);
            Assimp::DefaultLogger::kill();
        }

        static void LoadModelToGameObject(const char filePath[], const std::shared_ptr<GameObject>& parentObject);

    private:
        glm::mat4 ConvertToGLM(const aiMatrix4x4& aiMat);
        void DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, Quaternion rotation, glm::vec3& scale);
        void loadModel(const std::string& path, const std::shared_ptr<GameObject>& parent);

        void processNode(aiNode* node, const aiScene* scene, const std::shared_ptr<GameObject>& parent);

        void processMesh(aiMesh* mesh, const aiScene* scene, std::shared_ptr<GameObject> parent);

    };

}

