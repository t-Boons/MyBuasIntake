// Tygo Boons 2022

#pragma once

#include "Scene/Scene.h"

namespace Gameplay
{
	class TankGameManager
	{
	public:
		// Starts the tank game.
		static void StartGame();

		// Called when player dies.
		static void OnDie();
		
		// Called when all enemies are dead.
		static void OnWin();

		// Load the level by index.
		static void LoadLevel(uint32_t index);

	private:
		static std::vector<std::function<RefPtr<Core::Scene>()>> s_Levels;
		static uint32_t s_CurrentLevel;
	};
}