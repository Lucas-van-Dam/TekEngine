//
// Created by LucasvanDam on 11/06/2024.
//

#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP
#include <vector>
#include <memory>
#include "../Components/Renderer.hpp"


class RenderManager {
private:
    std::vector<std::shared_ptr<Renderer>> renderers;

public:
    void Render();
    void AddRenderer(const std::shared_ptr<Renderer> renderer);
};


#endif //RENDERMANAGER_HPP
