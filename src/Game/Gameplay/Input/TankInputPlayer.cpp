// 2022 Tygo Boons

#include "mypch.h"
#include "TankInputPlayer.h"
#include "Physics/Physics.h"

namespace Gameplay
{
	void TankInputPlayer::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();
	}

	void TankInputPlayer::UpdateInput()
	{
		auto hits = Physics::Physics::RayCast(GetComponent<Entity::Transform>()->GetPosition() + GetComponent<Entity::Transform>()->GetForward() * 2.0f, GetComponent<Entity::Transform>()->GetForward(), 1000);

		LOG(hits->HitObject->GetName())

		/// Movement input
		// Reset input.
		m_MovementInput = glm::vec2(0.0f, 0.0f);

		// Read all input.
		m_MovementInput.x = Core::Input::IsKeyHeld(Core::Input::Key::W) ? 1.0f : m_MovementInput.x;
		m_MovementInput.x = Core::Input::IsKeyHeld(Core::Input::Key::S) ? -1.0f : m_MovementInput.x;

		m_MovementInput.y = Core::Input::IsKeyHeld(Core::Input::Key::A) ? -1.0f : m_MovementInput.y;
		m_MovementInput.y = Core::Input::IsKeyHeld(Core::Input::Key::D) ? 1.0f  : m_MovementInput.y;

		// Normalize input if both values arent 0.
		if (m_MovementInput.x != 0 && m_MovementInput.y != 0)
		{
			m_MovementInput = glm::normalize(m_MovementInput);
		}

		/// Gun position input.
		// Get normalized tank position from 0,0 from bottom left to 1,1 top right.
		glm::vec2 tankPositionToScreenPosition = glm::vec2(m_Transform->GetPosition().z / PLAYFIELD_SIZE_Z, m_Transform->GetPosition().x / PLAYFIELD_SIZE_X);
		glm::vec2 center = (tankPositionToScreenPosition * 0.5f) + 0.5f;

		// Update guninput value.
		m_GunInput = glm::normalize(Core::Input::GetNormalizedMousePosition() - center);

		/// Is shooting input.
		// Update shooting input.
		m_Shoot = Core::Input::IsMouseButtonPressed(Core::Input::Button::Left);
	}
}