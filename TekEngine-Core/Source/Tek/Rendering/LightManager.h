#pragma once

#include "Tek/GameHierarchy/Components/Light.h"

namespace TEK {

    class LightManager : public std::enable_shared_from_this<LightManager> {
    public:
        LightManager(int maxLights);

        std::vector<std::shared_ptr<Light>> lights;
        int maxLights;
        void AddLight(const std::shared_ptr<Light>& light);
        std::shared_ptr<Light> mainLight;
    };

}

