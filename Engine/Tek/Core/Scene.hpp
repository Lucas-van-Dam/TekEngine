#ifndef SCENE_HPP
#define SCENE_HPP

#include "GameObject.hpp"
#include "memory"
#include "vector"


class Scene {
public:
    void AddGameObject(std::unique_ptr<GameObject> gameObject);
    void UpdateScene(float deltaTime);

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};


#endif //SCENE_HPP
