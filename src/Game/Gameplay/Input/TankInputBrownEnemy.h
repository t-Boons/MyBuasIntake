// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "TankInput.h"

#define MAX_WAIT_SHOOT_TIME 3.0f
#define MIN_WAIT_SHOOT_TIME 0.25f
#define RANDOM_GUN_DIRECTION_CHANGE_TIME 9.0f
#define GUN_ROTATION_SPEED_MAX_MULTIPLIER 0.8f

namespace Gameplay
{
	class TankInputBrownEnemy : public TankInput
	{

		IMPLEMENT_COMPONENT_IDENTIFIER_INHERIT(TankInputBrownEnemy, TankInput)

	public:
		virtual void StartInput() override;
		virtual void UpdateInput() override;

		// Start random shoot input.
		void StartShootInput();

		// Start random gun rotation input;
		void StartGunDirectionInput();

	private:
		float m_RotationMultiplier;
		float m_CurrentRotation;
		bool m_AimingAtEnemy;
		RefPtr<Entity::Transform> m_GunTransform;
	};
}