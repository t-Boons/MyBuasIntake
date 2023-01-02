// 2022 Tygo Boons

#include "mypch.h"

#include "TankInputBrownEnemy.h"

namespace Gameplay
{
	void TankInputBrownEnemy::UpdateInput()
	{
		// Reset shoot input.
		m_Shoot = false;

		// Make the run rotate around
		m_GunInput = glm::vec2(glm::sin(glm::pi<float>() * Core::Time::GetElapsedTime() * GUN_ROTATION_SPEED),
							   glm::cos(glm::pi<float>() * Core::Time::GetElapsedTime() * GUN_ROTATION_SPEED));

		// Increment timers
		m_Timer += Core::Time::GetDeltaTime();

		// Shoot if timer is higher than random value.
		if (m_Timer > m_RandomValue)
		{
			m_Timer = 0;

			// Get new random value.
			m_RandomValue = Utils::Random::Range(MIN_WAIT_SHOOT_TIME, MAX_WAIT_SHOOT_TIME);

			// Shoot
			m_Shoot = true;
		}
	}
}