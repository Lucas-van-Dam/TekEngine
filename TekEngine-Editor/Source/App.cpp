#include "Tek.h"

#include "imgui/imgui.h"

class EditorLayer : public TEK::Layer {
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

	void OnEvent(TEK::Event& event) override {
		//TEK_TRACE("{0}", event);
	}
};

class Editor : public TEK::Application
{
public:
	Editor() {
		PushLayer(new EditorLayer());
	}

	~Editor(){

	}
};

TEK::Application* TEK::CreateApplication() {
	return new Editor();
}