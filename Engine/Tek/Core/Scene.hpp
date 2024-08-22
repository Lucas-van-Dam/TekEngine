#ifndef SCENE_HPP
#define SCENE_HPP

#include "GameObject.hpp"
#include "memory"
#include "vector"
#include "EditorCamera.hpp"
#include "Components/Light.hpp"
#include "Rendering/LightManager.hpp"
#include "Rendering/RenderManager.hpp"


class Scene: public std::enable_shared_from_this<Scene> {
public:
    Scene();
    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    void UpdateScene(float deltaTime);
    void PrintSceneHierarchy();
    EditorCamera* GetEditorCamera();
    std::shared_ptr<EditorCamera> camera;
    std::shared_ptr<LightManager> lightManager;
    std::unique_ptr<RenderManager> renderManager;

private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};


#endif //SCENE_HPP
