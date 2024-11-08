#include "reonpch.h"
#include "Material.h"

namespace REON {

	Material::Material(std::shared_ptr<Shader> shader) : shader(std::move(shader)) {

	}

	Material::Material() {

	}

}