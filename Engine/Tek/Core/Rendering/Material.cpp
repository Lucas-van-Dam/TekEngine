#include "Material.hpp"

#include <utility>

Material::Material(std::shared_ptr<Shader> shader) : shader(std::move(shader)) {

}

Material::Material(){

}
