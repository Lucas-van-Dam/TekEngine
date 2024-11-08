#pragma once
#include "REON/Layer.h"

#include "REON/Core.h"

#include "REON/GameHierarchy/GameObject.h"

#include "REON/Events/KeyEvent.h"
#include "REON/Events/MouseEvent.h"

namespace REON {

	class GameLogicLayer : public Layer
	{
	public:
		GameLogicLayer();
		~GameLogicLayer();

		void OnDetach() override;
		void OnAttach() override;
		void OnUpdate() override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

		void InitializeTestScene();

		void CheckKeyPressed();
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);

	private:
		float deltaTime = 0.0f;
		std::chrono::high_resolution_clock::time_point lastTime;
		
	};

}

