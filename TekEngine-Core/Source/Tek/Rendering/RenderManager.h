#pragma once

#include "Tek/GameHierarchy/Components/Renderer.h"
#include "Tek/Rendering/LightManager.h"
#include "Tek/EditorCamera.h"



namespace TEK {
    class GameObject;

    class RenderManager {
    private:
        std::unordered_map<std::shared_ptr<Shader>, std::vector<std::shared_ptr<Renderer>>> shaderToRenderer;
        std::vector<std::shared_ptr<Renderer>> renderers;
        std::vector<int> depthCubeMaps;
        std::vector<unsigned int> additionalDepthFBOs;
        void RenderOpaques();
        void RenderTransparents();
        void RenderPostProcessing();
        void GenerateShadows();
        void GenerateMainLightShadows();
        void GenerateAdditionalShadows();
        void RenderSkyBox();

        std::shared_ptr<Shader> DirectionalShadowShader = std::make_shared<Shader>("DirectionalShadow.vert", "DirectionalShadow.frag");
        std::shared_ptr<Shader> AdditionalShadowShader = std::make_shared<Shader>("OmnidirectionalShadow.vert", "OmnidirectionalShadow.frag", "OmnidirectionalShadow.geom");
        unsigned int depthMapFBO;
        unsigned int depthMap;
        const unsigned int MAIN_SHADOW_WIDTH = 4096*2, MAIN_SHADOW_HEIGHT = 4096*2;
        const unsigned int ADDITIONAL_SHADOW_WIDTH = 1024, ADDITIONAL_SHADOW_HEIGHT = 1024;
        std::shared_ptr<LightManager> lightManager;
        std::shared_ptr<EditorCamera> camera;
        glm::mat4 mainLightView;
        glm::mat4 mainLightProj;
        std::vector<std::shared_ptr<Light>> pointLights;

        std::shared_ptr<Shader> screenShader = std::make_shared<Shader>("fullScreen.vert", "fullScreen.frag");
        float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f
        };
        unsigned int framebuffer, textureColorbuffer, rbo;
        unsigned int quadVAO, quadVBO;

        unsigned int skyboxVAO, skyboxVBO;
        unsigned int skyboxTexture;
        unsigned int hdrTexture;
        unsigned int irradianceMap;
        unsigned int prefilterMap;
        unsigned int brdfLUTTexture;
        std::shared_ptr<Shader> irradianceShader = std::make_shared<Shader>("CubeProjection.vert", "IrradianceMap.frag");
        std::shared_ptr<Shader> skyboxShader = std::make_shared<Shader>("SkyBox.vert", "SkyBox.frag");
        std::shared_ptr<Shader> skyboxMappingShader = std::make_shared<Shader>("CubeProjection.vert", "CubeProjection.frag");
        std::shared_ptr<Shader> preFilterShader = std::make_shared<Shader>("CubeProjection.vert", "PreFilter.frag");
        std::shared_ptr<Shader> brdfShader = std::make_shared<Shader>("brdf.vert", "brdf.frag");
        std::string skyboxLocation = "Assets/Textures/brown_photostudio_02_4k.hdr";
        void InitializeSkyBox();

#pragma region data
        std::vector<std::string> faces
        {
            "right.jpg",
                    "left.jpg",
                    "top.jpg",
                    "bottom.jpg",
                    "front.jpg",
                    "back.jpg"
        };
        float skyboxVertices[108] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };
#pragma endregion

    public:
        void Render();
        void AddRenderer(const std::shared_ptr<Renderer>& renderer);
        RenderManager(std::shared_ptr<LightManager> lightManager, std::shared_ptr<EditorCamera> camera);
        void Initialize();
        void HotReloadShaders();
    };

}

