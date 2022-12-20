// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"

// Note the z axis is sideways and x axis is up and down from the current view.

// Macro defines the size in Units of the playfield with the current view.
#define PLAYFIELD_SIZE_Z 25.79f
#define PLAYFIELD_SIZE_X 20.09f

namespace Gameplay
{
	class TankInput : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankInput)

	public:
		virtual void Start() override;
		virtual void Update() override;

		// Get current movement input.
		const glm::vec2& GetMovementInput() const { return m_MovementInput; }

		// Get current gun direction input.
		const glm::vec2& GetGunDirectionInput() const { return m_GunInput; }

	private:
		glm::vec2 m_MovementInput = glm::vec2(0.0f);
		glm::vec2 m_GunInput = glm::vec2(0.0f);

		RefPtr<Entity::Transform> m_Transform;
	};
}