#pragma once

#include "REON/Layer.h"

#include "REON/Core.h"
#include "REON/Events/KeyEvent.h"
#include "REON/Events/MouseEvent.h"

namespace REON {

	class RenderLayer : public Layer
	{
	public:
		RenderLayer();
		~RenderLayer();

		void OnDetach() override;
		void OnAttach() override;
		void OnUpdate() override;
		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

		bool ProcessKeyPress(KeyPressedEvent& event);
		void ProcessMouseMove();

	private:
		bool m_SceneHovered = false;
		double m_SavedX = 0, m_SavedY = 0;
		bool m_CursorLocked = false;
	};

}