#pragma once

#include "REON/GameHierarchy/Components/Light.h"

namespace REON {

    class LightManager : public std::enable_shared_from_this<LightManager> {
    public:
        LightManager(int maxLights);

        std::vector<std::shared_ptr<Light>> lights;
        int maxLights;
        void AddLight(const std::shared_ptr<Light>& light);
        std::shared_ptr<Light> mainLight;
    };

}

