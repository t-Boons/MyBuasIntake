// 2022 Tygo Boons 

#include "mypch.h"
#include "TankManager.h"
#include "TankGameManager.h"

namespace Gameplay
{
	void TankManager::SetEnemyCount(uint32_t count)
	{
		m_EnemyCount = count;
	}

	void TankManager::OnEnemyDie()
	{
		m_EnemyCount--;

		// Runs if all enemies are dead.
		if (m_EnemyCount <= 0)
		{
			TankGameManager::OnWin();
		}
	}

	void TankManager::OnPlayerDie()
	{
		TankGameManager::OnDie();
	}
}
