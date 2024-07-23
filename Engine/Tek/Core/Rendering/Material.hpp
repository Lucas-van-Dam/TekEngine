#ifndef MATERIAL_HPP
#define MATERIAL_HPP


#include <memory>
#include "Shader.hpp"

class Material {
private:

public:
    std::shared_ptr<Shader> shader;
    Material(std::shared_ptr<Shader> shader);
};


#endif //MATERIAL_HPP
