#ifndef LIGHTMANAGER_HPP
#define LIGHTMANAGER_HPP

#include <vector>
#include "../Components/Light.hpp"

class LightManager : public std::enable_shared_from_this<LightManager> {
public:
    LightManager(int maxLights);

    std::vector<std::shared_ptr<Light>> lights;
    int maxLights;
    void AddLight(std::shared_ptr<Light> light);
};


#endif //LIGHTMANAGER_HPP
