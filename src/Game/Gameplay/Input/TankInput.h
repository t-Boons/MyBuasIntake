// Tygo Boons 2022

#pragma once

#include "Game/Components.h"

#define START_INPUT_DELAY 5.0F

namespace Gameplay
{
	class TankInput : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankInput)

	public:
		virtual void Start() override;

		virtual void Update() override;

		// Upates the actual input
		virtual void UpdateInput() {}

		// Get movement input.
		const glm::vec2& GetMovementInput() const { return m_MovementInput; }

		// Get current gun direction input.
		const glm::vec2& GetGunDirectionInput() const { return m_GunInput; }

		// Get if should shoot.
		bool IsShooting() const { return m_Shoot; }

	protected:
		glm::vec2 m_MovementInput = glm::vec2(0.0f);
		glm::vec2 m_GunInput	  = glm::vec2(1.0f, 0.0f);
		bool m_Shoot			  = false;

	private:
		float m_Time;
	};
}