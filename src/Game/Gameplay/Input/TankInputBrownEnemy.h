// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "TankInput.h"

#define MAX_WAIT_SHOOT_TIME 7.0f
#define MIN_WAIT_SHOOT_TIME 1.0f
#define GUN_ROTATION_SPEED 0.3f

namespace Gameplay
{
	class TankInputBrownEnemy : public TankInput
	{

		IMPLEMENT_COMPONENT_IDENTIFIER_INHERIT(TankInputBrownEnemy, TankInput)

	public:
		virtual void UpdateInput() override;

	private:
		float m_Timer;
		float m_RandomValue;
	};
}