//
// Created by LucasvanDam on 01/07/2024.
//

#include "SceneManager.hpp"

std::shared_ptr<Scene> SceneManager::GetActiveScene() {
    static std::shared_ptr<Scene> activeScene = make_shared<Scene>();
    return activeScene;
}
