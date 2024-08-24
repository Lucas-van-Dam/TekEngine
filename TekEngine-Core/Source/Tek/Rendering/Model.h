#pragma once

#include "assimp/DefaultLogger.hpp"

namespace TEK {

    class Model {
    public:
        // model data
        std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> meshes;
        std::string directory;

        explicit Model(const char* path, const std::shared_ptr<GameObject>& parent) {
            Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
            Assimp::LogStream* stderrStream = Assimp::LogStream::createDefaultStream(aiDefaultLogStream_STDERR);
            Assimp::DefaultLogger::get()->attachStream(stderrStream, Assimp::Logger::NORMAL | Assimp::Logger::DEBUGGING |
                Assimp::Logger::VERBOSE);
            loadModel(path, parent);
            Assimp::DefaultLogger::kill();
        }

        void Draw(Shader& shader, std::vector<LightData> lightData);

        static void LoadModelToGameObject(const char filePath[], const std::shared_ptr<GameObject>& parentObject);

    private:
        void loadModel(const std::string& path, const std::shared_ptr<GameObject>& parent);

        void processNode(aiNode* node, const aiScene* scene, const std::shared_ptr<GameObject>& parent);

        std::shared_ptr<GameObject> processMesh(aiMesh* mesh, const aiScene* scene);

        std::shared_ptr<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
            const std::string& typeName);

    };

}

