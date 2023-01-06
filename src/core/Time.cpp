// 2022 Tygo Boons

#include "mypch.h"
#include "Time.h"

namespace Core
{
	Time* Time::s_Instance = new Time;

	Time::Time()
	{
		m_SfmlTimer = sf::Clock();
		m_ElapsedTime = 0;
		m_DeltaTime = 0;
		m_TimeScale = 1;
	}

	void Time::Tick()
	{
		// Tick game instance
		sf::Time dt = s_Instance->m_SfmlTimer.restart();

		// Set delta time variables.
		s_Instance->m_DeltaTime = dt.asSeconds() * s_Instance->m_TimeScale;
		s_Instance->m_RealDeltaTime = dt.asSeconds();

		// Update elapsed time.
		s_Instance->m_ElapsedTime += s_Instance->m_DeltaTime;
	}
}