#include "reonpch.h"
#include "RenderLayer.h"
#include "RenderManager.h"
#include "REON/GameHierarchy/SceneManager.h"
#include "REON/KeyCodes.h"
#include <imgui.h>
#include <GLFW/glfw3.h>
#include "REON/Application.h"
#include "REON/MouseButtonCodes.h"
#include "ImGuizmo.h"
#include <glm/gtc/type_ptr.hpp>
#include "REON/GameHierarchy/Components/Transform.h"

namespace REON {

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
		ProcessMouseMove();
		SceneManager::Get()->GetCurrentScene()->renderManager->Render();
	}

	void RenderLayer::OnImGuiRender()
	{
		/*ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

		if (ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse))
		{
			auto scene = SceneManager::Get()->GetCurrentScene();

			auto size = ImGui::GetContentRegionAvail();
			scene->renderManager->SetRenderDimensions(size.x, size.y);
			m_SceneHovered = ImGui::IsWindowHovered();

			ImGui::Image((void*)(intptr_t)scene->renderManager->GetEndBuffer(), size, ImVec2(0, 1), ImVec2(1, 0));

			ImVec2 windowSize = ImGui::GetWindowSize();
			ImVec2 pos = ImGui::GetWindowPos();

			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(pos.x, pos.y, windowSize.x, windowSize.y);

			glm::mat4 viewMatrix = scene->GetEditorCamera()->GetViewMatrix();
			glm::mat4 projMatrix = scene->GetEditorCamera()->GetProjectionMatrix();
			glm::mat4 objectMatrix = scene->GetGameObject(0)->GetTransform()->GetTransformationMatrix();

			if (ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projMatrix),
				ImGuizmo::TRANSLATE, ImGuizmo::WORLD, glm::value_ptr(objectMatrix)))
			{
				scene->GetGameObject(0)->GetTransform()->SetWorldTransform(objectMatrix);
			}
		}
		ImGui::End();

		ImGui::PopStyleVar(2);*/
	}

	void RenderLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(REON_BIND_EVENT_FN(RenderLayer::ProcessKeyPress));
	}

	bool RenderLayer::ProcessKeyPress(KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == REON_KEY_F2 && event.GetRepeatCount() == 0) {
			SceneManager::Get()->GetCurrentScene()->renderManager->HotReloadShaders();
		}
		return false;
	}

	void RenderLayer::ProcessMouseMove()
	{
		if (m_SceneHovered) {
			if (Input::IsMouseButtonPressed(REON_MOUSE_BUTTON_2)) {
				if (!m_CursorLocked) {
					glfwGetCursorPos((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), &m_SavedX, &m_SavedY);
					glfwSetInputMode((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				}
				
				float Xoffset = Input::GetMouseX() - (float)m_SavedX;
				float Yoffset = m_SavedY - Input::GetMouseY();
				SceneManager::Get()->GetCurrentScene()->GetEditorCamera()->ProcessMouseMovement(Xoffset, Yoffset);
				glfwSetCursorPos((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), m_SavedX, m_SavedY);
				m_CursorLocked = true;
			}
			else {
				glfwSetInputMode((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				m_CursorLocked = false;
			}
		}
	}
}