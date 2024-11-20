#pragma once

namespace REON {

    class GameObject;

    class Component {
    public:
        virtual ~Component() = default;
        virtual void Update(float deltaTime) = 0;
        //virtual void Initialize() = 0;

        std::shared_ptr<GameObject> GetOwner() const {
            return m_GameObject.lock();
        }

        virtual void SetOwner(std::shared_ptr<GameObject> owner) {
            m_GameObject = owner;
        }

        virtual void OnGameObjectAddedToScene() = 0;
        virtual void OnComponentDetach() = 0;

    private:
        std::weak_ptr<GameObject> m_GameObject;
    };
}

