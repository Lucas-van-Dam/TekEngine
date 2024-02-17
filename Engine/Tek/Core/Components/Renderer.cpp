#include "Renderer.hpp"

void Renderer::Draw() const {
    model->Draw(*shader);
}
