// 2022 Tygo Boons

#include "mypch.h"

#include "TankInput.h"
#include "Game/Components.h"

namespace Gameplay
{
	void TankInput::Start()
	{
		m_Time = 0;
	}

	void TankInput::Update()
	{

		// Sets a delay untill the input gets updated.
		if (m_Time < START_INPUT_DELAY)
		{
			m_Time += Core::Time::GetDeltaTime();
			return;
		}

		UpdateInput();
	}
}