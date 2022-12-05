// 2022 Tygo Boons

#include "mypch.h"
#include "TankMovement.h"
#include "Core/Game.h"
#include "Core/Time.h"
#include "Core/core.h"

using namespace Entity;

namespace Gameplay
{

	void TankMovement::Start()
	{
		m_Transform = GetComponent<Transform>();
	}

	void TankMovement::Update()
	{
		float dt = Core::Time::GetDeltaTime();
		m_Transform->Translate(sf::Keyboard::isKeyPressed(sf::Keyboard::T) ? m_Transform->GetForward() * dt * 25.0f : glm::vec3(0.0f));
		m_Transform->Translate(sf::Keyboard::isKeyPressed(sf::Keyboard::G) ? m_Transform->GetForward() * -dt * 25.0f : glm::vec3(0.0f));

		m_Transform->Rotate(sf::Keyboard::isKeyPressed(sf::Keyboard::F) ? glm::vec3(0, 1, 0) * dt * 50.0f : glm::vec3(0.0f));
		m_Transform->Rotate(sf::Keyboard::isKeyPressed(sf::Keyboard::H) ? glm::vec3(0, 1, 0) * -dt * 50.0f : glm::vec3(0.0f));
	}
}