#pragma once

namespace TEK {

    class GameObject;

    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime) = 0;
        //virtual void Initialize() = 0;

        std::shared_ptr<GameObject> GetOwner() const {
            return gameObject.lock();
        }

        virtual void SetOwner(std::shared_ptr<GameObject> owner) {
            gameObject = owner;
        }

        virtual void OnGameObjectAddedToScene();
        virtual void OnComponentDetach();

    private:
        std::weak_ptr<GameObject> gameObject;
    };
}

