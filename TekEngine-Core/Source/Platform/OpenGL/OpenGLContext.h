#pragma once

#include "Tek/Rendering/RenderContext.h"

struct GLFWwindow;

namespace TEK {

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