// 2022 Tygo Boons

#include "mypch.h"
#include "FlyingCamera.h"
#include "Core/Time.h"

namespace Utils
{
	glm::vec3 FlyingCamera::GetPositionDeltaFromInput()
	{
		glm::vec3 pos = { 0, 0, 0 };

		float deltaTime = Core::Time::GetDeltaTime();

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::W) ? glm::vec3(0.0f) : m_Camera->GetViewForward() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? glm::vec3(0.0f) : -m_Camera->GetViewForward() * (deltaTime * 10);

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? glm::vec3(0.0f) : m_Camera->GetViewRight() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? glm::vec3(0.0f) : -m_Camera->GetViewRight() * (deltaTime * 10);

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::E) ? glm::vec3(0.0f) : m_Camera->GetViewUp() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ? glm::vec3(0.0f) : -m_Camera->GetViewUp() * (deltaTime * 10);

		return pos;
	}

	glm::vec3 FlyingCamera::GetRotationDeltaFromInput()
	{
		glm::vec3 rotation = { 0, 0, 0 };

		glm::vec2 delta = (m_MouseDelta - glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) * 0.25f;

		m_MouseDelta = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			rotation.y += delta.x;
			rotation.x += delta.y;
		}

		return rotation;
	}


	void FlyingCamera::Update()
	{
		// Error check to see if the camera is assigned.
		if (!m_Camera)
		{
			LOG_ERROR("FlyingCamera camera is not assigned!")
			return;
		}

		// Update camera position.
		m_Camera->SetViewPoint(m_Camera->GetViewPoint() + GetPositionDeltaFromInput());

		// Update camera rotation;
		m_Camera->SetViewRotation(m_Camera->GetViewRotation() + GetRotationDeltaFromInput());
	}
}