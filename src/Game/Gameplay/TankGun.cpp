// 2022 Tygo Boons

#include "mypch.h"
#include "TankGun.h"
#include "Core/Game.h"
#include "Entity/GameObject.h"
#include "Game/Scenes/TankScenePrefabs.h"

namespace Gameplay
{
	void TankGun::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();

		// Get transform component from tank body.
		m_ParentTransform = Entity::GameObject::Find("PlayerTank")->GetComponent<Entity::Transform>();

		// Get tank input component from parent object (because the tank body object contains the tankinput component)
		m_Input = m_ParentTransform->GetComponent<TankInput>();
	}

	void TankGun::Update()
	{
		// Set position equal to tank body position.
		m_Transform->SetPosition(m_ParentTransform->GetPosition());

		SetGunRotation(m_Input->GetGunDirectionInput());


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (!m_HasTriggered)
			{
				// Spawn bullet.
				RefPtr<Entity::GameObject> bullet = Entity::GameObject::Instantiate(TankScenePrefabs::CreateBullet(),
					m_Transform->GetPosition() + m_Transform->GetForward() * 2.0f,
					m_Transform->GetRotation());

				m_HasTriggered = true;
			}
		}
		else
		{
			m_HasTriggered = false;
		}
	}

	void TankGun::SetGunRotation(const glm::vec2& direction)
	{
		// Calculate the angle based on the look direction.
		float angle = glm::acos(glm::dot(glm::vec2(0.0f, 1.0f), direction));
		angle = direction.x > 0 ? -angle : angle;

		// Rotate turret to right direction.
		m_Transform->SetRotation(glm::quat({ 0, angle + glm::radians(90.0f), 0 }));
	}
}