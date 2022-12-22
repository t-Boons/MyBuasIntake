// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "TankInput.h"

namespace Gameplay
{
	class TankInputBrownEnemy : public TankInput
	{
		IMPLEMENT_COMPONENT_IDENTIFIER_INHERIT(TankInputBrownEnemy, TankInput)

		// TODO Add actual AI to this.
	};
}