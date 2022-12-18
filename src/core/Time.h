// 2022 Tygo Boons

#pragma once

#include <SFML/Graphics.hpp>

namespace Core
{
	class Time
	{
	public:
		Time();

		// Update Time.
		static void	Tick();

		// Get Delta time.
		static float GetDeltaTime() { return s_Instance->m_DeltaTime; }

		// Get Elapsed time.
		static float GetElapsedTime() { return s_Instance->m_ElapsedTime; }

		// Get frames per second.
		static uint32_t GetFPS() { return static_cast<uint32_t>(1.0f / s_Instance->m_DeltaTime); }

	private:

		static Time* s_Instance;

		sf::Clock m_SfmlTimer;
		float m_DeltaTime;
		float m_ElapsedTime;
	};
}