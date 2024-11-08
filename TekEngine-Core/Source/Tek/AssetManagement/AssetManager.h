#pragma once

#include <any>

#include "Asset.h"

namespace TEK {

	class AssetManager
	{
	public:
		static AssetManager& GetInstance() {
			static AssetManager instance;
			return instance;
		}

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;

		template<typename AssetType>
		std::shared_ptr<AssetType> LoadAsset(const std::string& path, std::any metadata = {});

	private:
		AssetManager() = default;
		~AssetManager() = default;

		std::unordered_map<unsigned int, std::shared_ptr<Asset>> assets;
	};

	template<typename AssetType>
	std::shared_ptr<AssetType> AssetManager::LoadAsset(const std::string& path, std::any metadata)
	{
		unsigned int assetID = std::hash<std::string>{}(path);

		auto it = assets.find(assetID);
		if (it != assets.end()) {
			return std::dynamic_pointer_cast<AssetType>(it->second);
		}

		auto asset = std::make_shared<AssetType>();

		asset->Load(path);
		assets[assetID] = asset;

		return asset;
	}

}

