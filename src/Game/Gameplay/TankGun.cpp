// 2022 Tygo Boons

#include "mypch.h"
#include "TankGun.h"
#include "Core/Game.h"

namespace Gameplay
{
	void TankGun::Start()
	{
		// Get transform component from tank body.
		m_ParentTransform = Entity::GameObject::Find("TankPlayer")->GetComponent<Entity::Transform>();

		// Get this transform.
		m_Transform = GetComponent<Entity::Transform>();
	}

	void TankGun::Update()
	{
		// Set position equal to tank body position.
		m_Transform->SetPosition(m_ParentTransform->GetPosition());


		// Calculate angle
		sf::Vector2u screenSize = Core::Game::Get()->GetWindow()->getSize();
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*Core::Game::Get()->GetWindow());

		glm::vec2 normalizedPosition = { static_cast<float>(mousePosition.x) / static_cast<float>(screenSize.x),
										 static_cast<float>(mousePosition.y) / static_cast<float>(screenSize.y) };
		normalizedPosition -= 0.5f;

		float angle = glm::acos(glm::dot(glm::vec2(0, 1.0f), glm::normalize(normalizedPosition)));
		angle = normalizedPosition.x > 0 ? angle : -angle;


		// Rotate turret to right direction.
		m_Transform->SetRotation(glm::quat({ 0, angle - glm::radians(90.0f), 0}));
	}
}