#include "reonpch.h"
#include "SceneManager.h"

namespace REON {
	SceneManager::SceneManager()
	{
		currentScene = std::make_shared<Scene>();
	}

	SceneManager::~SceneManager()
	{
	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene()
	{
		return currentScene;
	}

	std::shared_ptr<SceneManager> SceneManager::Get()
	{
		static std::shared_ptr<SceneManager> instance = std::make_shared<SceneManager>();
		return instance;
	}
}
