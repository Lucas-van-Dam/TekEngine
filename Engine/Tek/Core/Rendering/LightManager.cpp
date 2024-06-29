#include "LightManager.hpp"

LightManager::LightManager(int maxLights): maxLights(maxLights) {

}

void LightManager::AddLight(const std::shared_ptr<Light>& light) {
    if(mainLight == nullptr && light->type == Directional){
        mainLight = light;
        lights.insert(lights.begin(), light);
        return;
    }
    lights.emplace_back(light);
}