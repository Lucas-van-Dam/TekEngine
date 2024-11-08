#pragma once

#include <any>

namespace TEK {

	class Asset
	{
    public:
        virtual ~Asset() = default;
        virtual void Load(const std::string& filePath, std::any metadata = {}) = 0; // Pure virtual function for loading assets
        virtual void Unload() = 0;
        const std::string& GetPath() const { return path; }

    protected:
        std::string path;
	};

}

