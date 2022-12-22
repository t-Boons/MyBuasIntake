// 2022 Tygo Boons

#include "mypch.h"
#include "TankMovement.h"

namespace Gameplay
{
	void TankMovement::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();
		m_TankInput = GetComponent<TankInput>();
	}

	void TankMovement::Update()
	{
		float dt = Core::Time::GetDeltaTime();

		glm::vec2 input = m_TankInput->GetMovementInput();

		// Update movement.
		m_Transform->Translate(input.x * m_Transform->GetForward() * dt * MOVEMENT_SPEED);
		m_Transform->Rotate(input.y * glm::vec3(0, 1, 0) * dt * -ROTATION_SPEED);
	}
}