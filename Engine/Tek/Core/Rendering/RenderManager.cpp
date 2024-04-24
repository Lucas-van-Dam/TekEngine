//
// Created by LucasvanDam on 11/06/2024.
//

#include "RenderManager.hpp"

void RenderManager::Render() {
    for(const auto& renderer : renderers){
        renderer->Draw();
    }
}

void RenderManager::AddRenderer(const std::shared_ptr<Renderer> renderer) {
    renderers.push_back(renderer);
}
