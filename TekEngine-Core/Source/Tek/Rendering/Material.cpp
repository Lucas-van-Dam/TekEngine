#include "tekpch.h"
#include "Material.h"

namespace TEK {

	Material::Material(std::shared_ptr<Shader> shader) : shader(std::move(shader)) {

	}

	Material::Material() {

	}

}