#pragma once
#include "Tek/Layer.h"

#include "Tek/Core.h"

#include "Tek/Events/KeyEvent.h"
#include "Tek/Events/MouseEvent.h"

namespace TEK {

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

	private:
		float deltaTime = 0.0f;
		std::chrono::high_resolution_clock::time_point lastTime;
	};

}

