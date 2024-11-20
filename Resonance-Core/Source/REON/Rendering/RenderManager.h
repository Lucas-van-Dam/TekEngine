#pragma once

#include "REON/GameHierarchy/Components/Renderer.h"
#include "REON/Rendering/LightManager.h"




namespace REON {
    class GameObject;
    class EditorCamera;

    class RenderManager {
    public:
        void Render();
        void AddRenderer(const std::shared_ptr<Renderer>& renderer);
        void RemoveRenderer(std::shared_ptr<Renderer> renderer);
        RenderManager(std::shared_ptr<LightManager> lightManager, std::shared_ptr<EditorCamera> camera);
        void Initialize();
        void HotReloadShaders();
        unsigned int GetEndBuffer();
        void SetRenderDimensions(int width, int height);
        int GetRenderWidth();
        int GetRenderHeight();

    private:
        void RenderOpaques();
        void RenderTransparents();
        void RenderPostProcessing();
        void GenerateShadows();
        void GenerateMainLightShadows();
        void GenerateAdditionalShadows();
        void RenderSkyBox();
        void InitializeSkyBox();

    private:
        int m_Width, m_Height;
        std::unordered_map<std::shared_ptr<Shader>, std::vector<std::shared_ptr<Renderer>>> m_ShaderToRenderer;
        std::vector<std::shared_ptr<Renderer>> m_Renderers;
        std::shared_ptr<EditorCamera> m_Camera;

        //Lighting
        std::shared_ptr<LightManager> m_LightManager;
        glm::mat4 m_MainLightView;
        glm::mat4 m_MainLightProj;
        std::vector<std::shared_ptr<Light>> m_PointLights;

        //Shadows
        unsigned int m_DepthMapFBO;
        unsigned int m_DepthMap;
        const unsigned int MAIN_SHADOW_WIDTH = 4096, MAIN_SHADOW_HEIGHT = 4096;
        const unsigned int ADDITIONAL_SHADOW_WIDTH = 1024, ADDITIONAL_SHADOW_HEIGHT = 1024;
        std::vector<int> m_DepthCubeMaps;
        std::vector<unsigned int> m_AdditionalDepthFBOs;
        std::shared_ptr<Shader> m_DirectionalShadowShader = std::make_shared<Shader>("DirectionalShadow.vert", "DirectionalShadow.frag");
        std::shared_ptr<Shader> m_AdditionalShadowShader = std::make_shared<Shader>("OmnidirectionalShadow.vert", "OmnidirectionalShadow.frag", "OmnidirectionalShadow.geom");

        //Skybox
        unsigned int m_SkyboxVAO, m_SkyboxVBO;
        unsigned int m_SkyboxTexture;
        unsigned int m_HdrTexture;
        unsigned int m_IrradianceMap;
        unsigned int m_PrefilterMap;
        unsigned int m_BrdfLUTTexture;
        std::shared_ptr<Shader> m_IrradianceShader = std::make_shared<Shader>("CubeProjection.vert", "IrradianceMap.frag");
        std::shared_ptr<Shader> m_SkyboxShader = std::make_shared<Shader>("SkyBox.vert", "SkyBox.frag");
        std::shared_ptr<Shader> m_SkyboxMappingShader = std::make_shared<Shader>("CubeProjection.vert", "CubeProjection.frag");
        std::shared_ptr<Shader> m_PreFilterShader = std::make_shared<Shader>("CubeProjection.vert", "PreFilter.frag");
        std::shared_ptr<Shader> m_BrdfShader = std::make_shared<Shader>("brdf.vert", "brdf.frag");
        std::string m_SkyboxLocation = "Assets/Textures/Black Outside.jpg";

        //Screen shader
        unsigned int m_Framebuffer, m_TextureColorbuffer, m_Rbo;
        unsigned int m_QuadVAO, m_QuadVBO;
        std::shared_ptr<Shader> m_ScreenShader = std::make_shared<Shader>("fullScreen.vert", "fullScreen.frag");
        float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f
        };

#pragma region data
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
    };

}

