// Tygo Boons 2022

#include "mypch.h"
#include "TankInput.h"

namespace Gameplay
{
	void TankInput::Start()
	{
		// Get transform component.
		m_Transform = GetComponent<Entity::Transform>();
	}

	void TankInput::Update()
	{
		// Update input.
		m_MovementInput = glm::vec2(0.0f, 0.0f);

		// Read all input.
		m_MovementInput.x = sf::Keyboard::isKeyPressed(sf::Keyboard::Up)	? 1.0f  : m_MovementInput.x;
		m_MovementInput.x = sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  ? -1.0f : m_MovementInput.x;

		m_MovementInput.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  ? -1.0f : m_MovementInput.y;
		m_MovementInput.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? 1.0f  : m_MovementInput.y;

		// Normalize input if both values arent 0.
		if (m_MovementInput.x != 0 && m_MovementInput.y != 0)
		{
			m_MovementInput = glm::normalize(m_MovementInput);
		}



		// Get normalized tank position from 0,0 from bottom left to 1,1 top right.
		glm::vec2 tankPositionToScreenPosition = glm::vec2(m_Transform->GetPosition().z / PLAYFIELD_SIZE_Z, m_Transform->GetPosition().x / PLAYFIELD_SIZE_X);
		glm::vec2 center = (tankPositionToScreenPosition * 0.5f) + 0.5f;

		// Update guninput value.
		m_GunInput = glm::normalize(Core::Game::Get()->GetNormalizedMousePosition() - center);
	}
}