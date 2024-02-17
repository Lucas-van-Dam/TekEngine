#ifndef RENDERER_HPP
#define RENDERER_HPP


#include "../Rendering/Model.hpp"
#include "memory"
#include "vector"

class Renderer {
public:
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;
    void Draw() const;

private:


};


#endif //RENDERER_HPP
