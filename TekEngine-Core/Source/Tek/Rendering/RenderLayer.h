#pragma once

#include "Tek/Layer.h"

#include "Tek/Core.h"
#include <Tek/Events/KeyEvent.h>

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

		void Begin();
		void End();
	};

}