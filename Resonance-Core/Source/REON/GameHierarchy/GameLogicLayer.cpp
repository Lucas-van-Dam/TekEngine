#include "reonpch.h"
#include "GameLogicLayer.h"

#include "REON/GameHierarchy/SceneManager.h"
#include "REON/Rendering/Model.h"
#include "REON/GameHierarchy/Components/Transform.h"
#include "REON/GameHierarchy/Components/Light.h"
#include "REON/Application.h"

#include "REON/KeyCodes.h"
#include "REON/MouseButtonCodes.h"
#include <GLFW/glfw3.h>

namespace REON {

	GameLogicLayer::GameLogicLayer()
	{
	}

	GameLogicLayer::~GameLogicLayer()
	{

	}

	void GameLogicLayer::OnDetach()
	{

	}

	void GameLogicLayer::OnAttach()
	{
		InitializeTestScene();
		lastTime = std::chrono::high_resolution_clock::now();
	}

	void GameLogicLayer::OnUpdate()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		CheckKeyPressed();
		SceneManager::Get()->GetCurrentScene()->UpdateScene(deltaTime);
	}

	void GameLogicLayer::OnImGuiRender()
	{

	}

	void GameLogicLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<MouseMovedEvent>(REON_BIND_EVENT_FN(GameLogicLayer::OnMouseMoved));
		dispatcher.Dispatch<KeyPressedEvent>(REON_BIND_EVENT_FN(GameLogicLayer::OnKeyPressed));
	}


	void GameLogicLayer::InitializeTestScene()
	{
		char path[] = "Assets/Models/test/GoldStarBake2.gltf";

		// PBR_Textures_ORCA

		//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

		std::shared_ptr<GameObject> backPack = std::make_shared<GameObject>();

		std::shared_ptr<Scene> m_Scene = SceneManager::Get()->GetCurrentScene();

		m_Scene->AddGameObject(backPack);
		Model::LoadModelToGameObject(path, backPack);



		//    std::shared_ptr<GameObject> cube = std::make_shared<GameObject>();
		//    scene->AddGameObject(cube);
		//    Model::LoadModelToGameObject(path, cube);
		////
		//    cube->GetTransform()->localPosition = glm::vec3(0.0f, 7.5f, 0.0f);
		//    cube->GetTransform()->localScale = glm::vec3(0.5f, 0.5f, 0.5f);
		//    cube->GetTransform()->localRotation.setFromEulerAngles(0.0f, 12.5f, 0.0f);

		backPack->GetTransform()->localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		//backPack->GetTransform()->localScale = glm::vec3(0.01f, 0.01f, 0.01f);

		std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
		std::shared_ptr<Light> lightComponent = std::make_shared<Light>(LightType::Point, 10, glm::vec3(30.0f, 0.5f, 0.5f));
		m_Scene->AddGameObject(light);
		light->AddComponent<Light>(lightComponent);
		light->GetTransform()->localPosition = glm::vec3(-7, 3, 3);
		m_Scene->lightManager->AddLight(lightComponent);

		std::shared_ptr<GameObject> light2 = std::make_shared<GameObject>();
		std::shared_ptr<Light> lightComponent2 = std::make_shared<Light>(LightType::Point, 3, glm::vec3(1.0f, 1.0f, 1.0f));
		m_Scene->AddGameObject(light2);
		light2->AddComponent<Light>(lightComponent2);
		light2->GetTransform()->localPosition = glm::vec3(-5, 4, 3);
		m_Scene->lightManager->AddLight(lightComponent2);

		std::shared_ptr<GameObject> light4 = std::make_shared<GameObject>();
		std::shared_ptr<Light> lightComponent4 = std::make_shared<Light>(LightType::Directional, 3, glm::vec3(1, 1, 1));
		m_Scene->AddGameObject(light4);
		light4->AddComponent<Light>(lightComponent4);
		light4->GetTransform()->localRotation.setFromEulerAngles(110, 0, 0);
		m_Scene->lightManager->AddLight(lightComponent4);
	}

	void GameLogicLayer::CheckKeyPressed()
	{
		if (!Input::IsMouseButtonPressed(REON_MOUSE_BUTTON_2))
			return;
		auto camera = SceneManager::Get()->GetCurrentScene()->GetEditorCamera();

		if (Input::IsKeyPressed(REON_KEY_W)) {
			camera->ProcessKeyboard(FORWARD, deltaTime);
		}
		if (Input::IsKeyPressed(REON_KEY_D)) {
			camera->ProcessKeyboard(RIGHT, deltaTime);
		}
		if (Input::IsKeyPressed(REON_KEY_S)) {
			camera->ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (Input::IsKeyPressed(REON_KEY_A)) {
			camera->ProcessKeyboard(LEFT, deltaTime);
		}
		if (Input::IsKeyPressed(REON_KEY_E)) {
			camera->ProcessKeyboard(UP, deltaTime);
		}
		if (Input::IsKeyPressed(REON_KEY_Q)) {
			camera->ProcessKeyboard(DOWN, deltaTime);
		}
		
		camera->ProcessShiftKey(Input::IsKeyPressed(REON_KEY_LEFT_SHIFT));
	}

	bool GameLogicLayer::OnMouseMoved(MouseMovedEvent& event)
	{
		return false;
	}
	bool GameLogicLayer::OnKeyPressed(KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == REON_KEY_DELETE && event.GetRepeatCount() == 0) {
			auto obj = SceneManager::Get()->GetCurrentScene()->GetGameObject(0);
			if (obj != nullptr) {
				SceneManager::Get()->GetCurrentScene()->DeleteGameObject(obj);
			}
		}
		return false;
	}
}