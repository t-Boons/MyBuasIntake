// 2022 Tygo Boons

#include "mypch.h"
#include "DefaultScene.h"
#include "Game/Gameplay/TankGameManager.h"

namespace Gameplay
{
	void DefaultScene::LoadScene()
	{
		// Start the game.
		TankGameManager::StartGame();
	}
}