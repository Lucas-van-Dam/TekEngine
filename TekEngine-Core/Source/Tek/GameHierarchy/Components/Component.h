#pragma once

#include "Tek/GameHierarchy/GameObject.h"

namespace TEK {

    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime) = 0;
        //virtual void Initialize() = 0;
        std::shared_ptr<GameObject> gameObject;

        virtual void OnGameObjectAddedToScene();
    };
}

