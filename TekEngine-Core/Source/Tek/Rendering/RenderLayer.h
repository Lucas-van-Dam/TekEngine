#pragma once

#include "Tek/Layer.h"

#include "Tek/Core.h"

namespace TEK {

	class RenderLayer : public Layer
	{
	public:
		RenderLayer();
		~RenderLayer();

		void OnDetach() override;
		void OnAttach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	};

}