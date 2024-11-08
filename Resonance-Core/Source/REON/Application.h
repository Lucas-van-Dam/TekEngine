#pragma once
#include "REON/Core.h"
#include "REON/Events/Event.h"
#include "REON/Window.h"

#include "REON/Events/ApplicationEvent.h"
#include "REON/LayerStack.h"

#include "REON/ImGui/ImGuiLayer.h"
#include "Rendering/RenderLayer.h"
#include "GameHierarchy/GameLogicLayer.h"

namespace REON {

	class  Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		RenderLayer* m_RenderLayer;
		GameLogicLayer* m_GameLogicLayer;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}

