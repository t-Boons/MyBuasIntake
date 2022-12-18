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

		UpdateGunRotation();
	}

	void TankGun::UpdateGunRotation()
	{
		// Get the normalized look direction the tank gun should look at.
		glm::vec2 lookDirection = glm::normalize(Core::Game::Get()->GetNormalizedMousePosition() - GetNormalizedTankPosition());

		// Calculate the angle based on the look direction.
		float angle = glm::acos(glm::dot(glm::vec2(0.0f, 1.0f), lookDirection));
		angle = lookDirection.x > 0 ? -angle : angle;

		// Rotate turret to right direction.
		m_Transform->SetRotation(glm::quat({ 0, angle + glm::radians(90.0f), 0 }));
	}

	glm::vec2 TankGun::GetNormalizedTankPosition() const
	{
		// Get normalized tank position from 0,0 from bottom left to 1,1 top right.
		glm::vec2 tankPositionToScreenPosition = glm::vec2(m_ParentTransform->GetPosition().z / PLAYFIELD_SIZE_Z, m_ParentTransform->GetPosition().x / PLAYFIELD_SIZE_X);
		glm::vec2 center = (tankPositionToScreenPosition * 0.5f) + 0.5f;

		return center;
	}
}