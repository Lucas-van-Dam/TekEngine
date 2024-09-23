#include "tekpch.h"
#include "RenderLayer.h"
#include "RenderManager.h"
#include "Tek/GameHierarchy/SceneManager.h"
#include "Tek/KeyCodes.h"

namespace TEK {

	RenderLayer::RenderLayer()
	{

	}

	RenderLayer::~RenderLayer()
	{

	}

	void RenderLayer::OnDetach()
	{

	}

	void RenderLayer::OnAttach()
	{

	}

	void RenderLayer::OnUpdate()
	{
		SceneManager::Get()->GetCurrentScene()->renderManager->Render();
	}

	void RenderLayer::OnImGuiRender()
	{

	}

	void RenderLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(TEK_BIND_EVENT_FN(RenderLayer::ProcessKeyPress));
	}

	bool RenderLayer::ProcessKeyPress(KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == TEK_KEY_F2 && event.GetRepeatCount() == 0) {
			SceneManager::Get()->GetCurrentScene()->renderManager->HotReloadShaders();
		}
		return false;
	}

	void RenderLayer::Begin()
	{

	}

	void RenderLayer::End()
	{

	}

}