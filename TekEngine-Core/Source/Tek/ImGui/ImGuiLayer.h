#pragma once

#include "Tek/Layer.h"

#include "Tek/Events/ApplicationEvent.h"
#include "Tek/Events/MouseEvent.h"
#include "Tek/Events/KeyEvent.h"

#include "Tek/Core.h"


namespace TEK {

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnDetach() override;
		void OnAttach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}