// 2022 Tygo Boons
#include "TankMovement.h"
#include "Core/Game.h"

using namespace Entity;

namespace Gameplay
{

	void TankMovement::Start()
	{
		m_Transform = GetComponent<Transform>();
	}

	void TankMovement::Update()
	{
		m_Transform->Translate(sf::Keyboard::isKeyPressed(sf::Keyboard::T) ? m_Transform->GetForward() * 0.1f : glm::vec3(0.0f));
		m_Transform->Translate(sf::Keyboard::isKeyPressed(sf::Keyboard::G) ? m_Transform->GetForward() * -0.1f : glm::vec3(0.0f));

		m_Transform->Rotate(sf::Keyboard::isKeyPressed(sf::Keyboard::F) ? glm::vec3(0, 1, 0) * 0.1f : glm::vec3(0.0f));
		m_Transform->Rotate(sf::Keyboard::isKeyPressed(sf::Keyboard::H) ? glm::vec3(0, 1, 0) * -0.1f : glm::vec3(0.0f));

		LOG(m_Transform->GetPosition().x);
	}
}