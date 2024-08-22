#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP


#include <memory>
#include "Scene.hpp"

class SceneManager {
public:
    static std::shared_ptr<Scene> GetActiveScene();
};


#endif //SCENEMANAGER_HPP
