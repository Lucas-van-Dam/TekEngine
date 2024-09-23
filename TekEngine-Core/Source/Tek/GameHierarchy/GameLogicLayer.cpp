#include "tekpch.h"
#include "GameLogicLayer.h"

#include "Tek/GameHierarchy/GameObject.h"
#include "Tek/GameHierarchy/SceneManager.h"
#include "Tek/Rendering/Model.h"
#include "Tek/GameHierarchy/Components/Transform.h"
#include "Tek/GameHierarchy/Components/Light.h"

#include "Tek/KeyCodes.h"

namespace TEK {

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
		dispatcher.Dispatch<MouseMovedEvent>(TEK_BIND_EVENT_FN(GameLogicLayer::OnMouseMoved));
	}


	void GameLogicLayer::InitializeTestScene()
	{
		char path[] = "Assets/Models/SPHERES/untitled.gltf";

		//std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

		std::shared_ptr<GameObject> backPack = std::make_shared<GameObject>();

		std::shared_ptr<Scene> m_Scene = SceneManager::Get()->GetCurrentScene();

		m_Scene->AddGameObject(backPack);
		Model::LoadModelToGameObject(path, backPack);
		m_Scene->PrintSceneHierarchy();

		//    std::shared_ptr<GameObject> cube = std::make_shared<GameObject>();
		//    scene->AddGameObject(cube);
		//    Model::LoadModelToGameObject(path, cube);
		////
		//    cube->GetTransform()->localPosition = glm::vec3(0.0f, 7.5f, 0.0f);
		//    cube->GetTransform()->localScale = glm::vec3(0.5f, 0.5f, 0.5f);
		//    cube->GetTransform()->localRotation.setFromEulerAngles(0.0f, 12.5f, 0.0f);

		backPack->GetTransform()->localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		//backPack->GetTransform()->localScale = glm::vec3(0.5f, 0.5f, 0.5f);

		std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
		std::shared_ptr<Light> lightComponent = std::make_shared<Light>(LightType::Point, 3, glm::vec3(300.0f, 300.0f, 300.0f));
		m_Scene->AddGameObject(light);
		light->AddComponent<Light>(lightComponent);
		light->GetTransform()->localPosition = glm::vec3(-7, 3, 3);
		m_Scene->lightManager->AddLight(lightComponent);

		std::shared_ptr<GameObject> light2 = std::make_shared<GameObject>();
		std::shared_ptr<Light> lightComponent2 = std::make_shared<Light>(LightType::Point, 3, glm::vec3(30.0f, 300.0f, 30.0f));
		m_Scene->AddGameObject(light2);
		light2->AddComponent<Light>(lightComponent2);
		light2->GetTransform()->localPosition = glm::vec3(-5, 4, 3);
		m_Scene->lightManager->AddLight(lightComponent2);

		std::shared_ptr<GameObject> light4 = std::make_shared<GameObject>();
		std::shared_ptr<Light> lightComponent4 = std::make_shared<Light>(LightType::Directional, 10, glm::vec3(10, 10, 10));
		m_Scene->AddGameObject(light4);
		light4->AddComponent<Light>(lightComponent4);
		light4->GetTransform()->localRotation.setFromEulerAngles(90, 0, 0);
		m_Scene->lightManager->AddLight(lightComponent4);
	}

	void GameLogicLayer::CheckKeyPressed()
	{
		if (Input::IsKeyPressed(TEK_KEY_W)) {
			SceneManager::Get()->GetCurrentScene()->GetEditorCamera()->ProcessKeyboard(FORWARD, deltaTime);
		}
		if (Input::IsKeyPressed(TEK_KEY_D)) {
			SceneManager::Get()->GetCurrentScene()->GetEditorCamera()->ProcessKeyboard(RIGHT, deltaTime);
		}
		if (Input::IsKeyPressed(TEK_KEY_S)) {
			SceneManager::Get()->GetCurrentScene()->GetEditorCamera()->ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (Input::IsKeyPressed(TEK_KEY_A)) {
			SceneManager::Get()->GetCurrentScene()->GetEditorCamera()->ProcessKeyboard(LEFT, deltaTime);
		}
		if (Input::IsKeyPressed(TEK_KEY_E)) {
			SceneManager::Get()->GetCurrentScene()->GetEditorCamera()->ProcessKeyboard(UP, deltaTime);
		}
		if (Input::IsKeyPressed(TEK_KEY_Q)) {
			SceneManager::Get()->GetCurrentScene()->GetEditorCamera()->ProcessKeyboard(DOWN, deltaTime);
		}
	}

	bool GameLogicLayer::OnMouseMoved(MouseMovedEvent& event)
	{
		static float lastX = 0;
		static float lastY = 0;
		float Xoffset = event.GetX() - lastX;
		float Yoffset = lastY - event.GetY();
		lastX = event.GetX();
		lastY = event.GetY();
		SceneManager::Get()->GetCurrentScene()->GetEditorCamera()->ProcessMouseMovement(Xoffset, Yoffset);

		return false;
	}

}