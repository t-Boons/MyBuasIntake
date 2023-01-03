// 2023 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "TankInput.h"

#define RANDOM_DIRECTION_MAX_DELAY 4.5f
#define RANDOM_SHOOT_MAX_DELAY 3.5f
#define RANDOM_GUN_DIRECTION_MAX_DELAY 3.5f
#define MOVEMENT_SPEED_MULTIPLIER 0.75f

namespace Gameplay
{
	class TankInputAshEnemy : public TankInput
	{

		IMPLEMENT_COMPONENT_IDENTIFIER_INHERIT(TankInputAshEnemy, TankInput)

	public:
		virtual void StartInput() override;
		virtual void UpdateInput() override;

		// Start and update randomized inputs.
		void StartShootInput();
		void StartMovementInput();
		void StartGunDirectionInput();

		// Update Gun to player direction.
		void UpdateGunToPlayerDirection();

		// Update if the player is seen.
		void UpdatePlayerSpotted();

		// Updates the gun direction movement smoothly.
		void UpdateGunMovementInterpolation();

		// Lock the gun on to the player
		void LockOnToPlayer(bool lock);

	private:
		glm::vec3 m_GunToPlayerDirection;
		glm::vec2 m_NewGunInput;
		bool m_PlayerSpotted, m_LockedOnPlayer;
		float m_GunTransitionProgress;
	};
}