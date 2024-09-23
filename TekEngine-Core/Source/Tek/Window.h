#pragma once

#include "Tek/Core.h"

#include "Tek/Events/Event.h"

namespace TEK {

	struct WindowProperties {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "TekEngine",
			unsigned int width = 800,
			unsigned int height = 600)
			: Title(title), Width(width), Height(height) {}
	};

	class Window {
	public:
		using EventCallBackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};

}