#include "Reon.h"

#include "imgui/imgui.h"

class EditorLayer : public REON::Layer {
public:
	EditorLayer()
		: Layer("Editor") {}

	void OnUpdate() override {
		//TEK_INFO("EDITOR UPDATE");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test"); 
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(REON::Event& event) override {
		//TEK_TRACE("{0}", event);
	}
};

class Editor : public REON::Application
{
public:
	Editor() {
		PushLayer(new EditorLayer());
	}

	~Editor(){

	}
};

REON::Application* REON::CreateApplication() {
	return new Editor();
}