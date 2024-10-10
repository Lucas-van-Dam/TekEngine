#pragma once

#include "Tek/Layer.h"

#include "Tek/Core.h"
#include "Tek/Events/KeyEvent.h"
#include "Tek/Events/MouseEvent.h"

namespace TEK {

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
		double m_SavedX, m_SavedY;
		bool m_CursorLocked;
	};

}