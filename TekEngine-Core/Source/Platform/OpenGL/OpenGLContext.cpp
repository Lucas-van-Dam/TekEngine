#include "tekpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>

TEK::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	TEK_CORE_ASSERT(windowHandle, "Window handle is null")
}

void TEK::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	TEK_CORE_ASSERT(status, "Failed to initialize GLAD");
}

void TEK::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
