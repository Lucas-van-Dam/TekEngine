#include "tekpch.h"
#include "RenderLayer.h"
#include "RenderManager.h"
#include "Tek/GameHierarchy/SceneManager.h"

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

	void RenderLayer::Begin()
	{

	}

	void RenderLayer::End()
	{

	}

}