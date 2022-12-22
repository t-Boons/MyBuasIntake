// 2022 Tygo Boons

#include "mypch.h"
#include "FlyingCamera.h"
#include "Core/Input.h"

namespace Gameplay
{
	glm::vec3 FlyingCamera::GetPositionDeltaFromInput()
	{
		glm::vec3 pos = { 0, 0, 0 };

		float deltaTime = Core::Time::GetDeltaTime();

		// Update position values.
		pos += Core::Input::IsKeyHeld(Core::Input::Key::T) ? glm::vec3(0.0f) : m_Camera->GetViewForward() * (deltaTime * 10);
		pos += Core::Input::IsKeyHeld(Core::Input::Key::G) ? glm::vec3(0.0f) : -m_Camera->GetViewForward() * (deltaTime * 10);

		pos += Core::Input::IsKeyHeld(Core::Input::Key::H) ? glm::vec3(0.0f) : m_Camera->GetViewRight() * (deltaTime * 10);
		pos += Core::Input::IsKeyHeld(Core::Input::Key::F) ? glm::vec3(0.0f) : -m_Camera->GetViewRight() * (deltaTime * 10);

		pos += Core::Input::IsKeyHeld(Core::Input::Key::Y) ? glm::vec3(0.0f) : m_Camera->GetViewUp() * (deltaTime * 10);
		pos += Core::Input::IsKeyHeld(Core::Input::Key::R) ? glm::vec3(0.0f) : -m_Camera->GetViewUp() * (deltaTime * 10);

		return pos;
	}

	glm::vec3 FlyingCamera::GetRotationDeltaFromInput()
	{
		glm::vec3 rotation = { 0, 0, 0 };

		// Calculate mouse movmement delta.
		glm::vec2 delta = (m_MouseDelta - glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) * 0.25f;

		m_MouseDelta = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };

		// Assign movement when pressing right button on yuur mouse.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			rotation.y += delta.x;
			rotation.x += delta.y;
		}

		return rotation;
	}

	void FlyingCamera::Start()
	{
		m_Camera = GetComponent<Entity::Camera>();
		m_ActiveCamera = Core::Game::Get()->GetSceneManager()->GetActiveScene()->GetActiveCamera();

		// See if the flycam camera is the active camera
		m_IsActiveCamera = m_Camera == m_ActiveCamera;

		// Log error if camera can not be found.
		if (!m_Camera)
		{
			LOG_ERROR(GAMEOBJECT_IDENTITY + "FlyingCamera camera component can not be found.")
		}

		// Log if spectator camera is being used.
		if (m_IsActiveCamera)
		{
			LOG_INFO("Using spectator camera.")
		}
	}

	void FlyingCamera::Update()
	{
		// Error check to see if the camera is assigned.
		if (!m_IsActiveCamera)
		{
			return;
		}

		// Update camera position.
		m_Camera->SetViewPoint(m_Camera->GetViewPoint() + GetPositionDeltaFromInput());

		// Update camera rotation;
		m_Camera->SetViewRotation(m_Camera->GetViewRotation() + GetRotationDeltaFromInput());
	}
}