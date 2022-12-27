// Tygo Boons 2022

#include "mypch.h"
#include "TankGameManager.h"
#include "Core/Game.h"

#include "Game/Scenes/Level1.h"
#include "Game/Scenes/Level2.h"

namespace Gameplay
{
	std::vector<std::function<RefPtr<Core::Scene>()>> TankGameManager::s_Levels;
	uint32_t TankGameManager::s_CurrentLevel = 0;

	void TankGameManager::LoadLevel(uint32_t index)
	{
		Core::Game::Get()->GetSceneManager()->SetActiveScene(s_Levels[s_CurrentLevel]());
	}

	void TankGameManager::StartGame()
	{
		// Get all levels.
		s_Levels.push_back([]() {return std::static_pointer_cast<Core::Scene>(Level1::Create()); });
		s_Levels.push_back([]() {return std::static_pointer_cast<Core::Scene>(Level2::Create()); });



		// Load first level.
		s_CurrentLevel = 0;
		LoadLevel(s_CurrentLevel);
	}

	void TankGameManager::OnDie()
	{
		LOG_WARN("Player Lost. Loading first level.")
		s_CurrentLevel = 0;
		LoadLevel(s_CurrentLevel);
	}

	void TankGameManager::OnWin()
	{
		LOG_WARN("Player Won. Loading next level.")
		s_CurrentLevel++;
		LoadLevel(s_CurrentLevel);
	}
}