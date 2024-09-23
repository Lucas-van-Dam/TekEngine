#pragma once

#include "Tek/Window.h"

#include "Tek/Logger.h"

#include "GLFW/glfw3.h"
#include <Tek/Rendering/RenderContext.h>

namespace TEK {

	class  WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallBackFn& callback) override { m_Data.EventCallBack = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProperties& properties);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window;

		RenderContext* m_Context;

		struct WindowData {
			std::string Title;
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			EventCallBackFn EventCallBack;
		};

		WindowData m_Data;
	};

}

