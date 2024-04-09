#include "LightManager.hpp"

LightManager::LightManager(int maxLights): maxLights(maxLights) {

}

void LightManager::AddLight(std::shared_ptr<Light> light) {
    lights.emplace_back(light);
}