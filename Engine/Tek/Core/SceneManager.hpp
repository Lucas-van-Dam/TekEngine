#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP


#include <memory>
#include "Scene.hpp"

class SceneManager {
public:
    std::shared_ptr<Scene> activeScene;
};


#endif //SCENEMANAGER_HPP
