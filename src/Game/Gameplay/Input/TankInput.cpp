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
		// Reset shooting state;
		if (!m_FramePassed)
		{
			m_FramePassed = true;
		}
		else
		{
			m_Shoot = false;
		}

		// Sets a delay untill the input gets updated.
		if (m_Time < START_INPUT_DELAY)
		{
			m_Time += Core::Time::GetDeltaTime();
			return;
		}

		// Call start input method once when the input starts.
		if (!m_InputStarted)
		{
			m_InputStarted = true;
			StartInput();
		}

		UpdateInput();
	}

	void TankInput::Shoot()
	{
		m_Shoot = true;
		m_FramePassed = false;
	}
}