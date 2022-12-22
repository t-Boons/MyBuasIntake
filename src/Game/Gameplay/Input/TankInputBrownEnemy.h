// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "TankInput.h"

#define MAX_STATE_TIME 3.0f

namespace Gameplay
{
	class TankInputBrownEnemy : public TankInput
	{

		IMPLEMENT_COMPONENT_IDENTIFIER_INHERIT(TankInputBrownEnemy, TankInput)

	public:
		void Update() override;

		void RandomizeInputs();

	private:
		float m_Timer;
		float m_RandomValue;
	};
}