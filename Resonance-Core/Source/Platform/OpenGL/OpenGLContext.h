#pragma once

#include "REON/Rendering/RenderContext.h"

struct GLFWwindow;

namespace REON {

	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}