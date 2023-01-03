// 2022 Tygo Boons 

#include "mypch.h"
#include "TankManager.h"
#include "TankGameManager.h"
#include "Bullet.h"
#include "Game/Gameplay/Input/TankInput.h"

namespace Gameplay
{
	void TankManager::Start()
	{
		// Create audio source instances.
		m_WinSound = Entity::AudioSource::Create();
		m_WinSound->LoadClipFromFile("Assets/Audio/Effects/RoundWin.ogg");
		m_WinSound->SetVolume(0.7f);

		m_LoseSound = Entity::AudioSource::Create();
		m_LoseSound->LoadClipFromFile("Assets/Audio/Effects/RoundLose.ogg");
		m_LoseSound->SetVolume(0.7f);
	}

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
			Utils::TimedEvent e(2.1f, [=]()
				{
					TankGameManager::OnWin();
				});

			EndGameplayInScene();

			m_WinSound->Play();
		}
	}

	void TankManager::OnPlayerDie()
	{
		Utils::TimedEvent e(2.6f, [=]()
			{
				TankGameManager::OnDie();
			});

		EndGameplayInScene();

		m_LoseSound->Play();
	}

	void TankManager::EndGameplayInScene()
	{
		// Delete main music
		Entity::GameObject::Find("Music")->Destroy();

		// Delete tank input components in the scene.
		auto tankInputControllers = Entity::GameObject::FindObjectsOfType<TankInput>();
		for (auto& tic : tankInputControllers)
		{
			tic->Destroy();
		}

		// Destroy bullets
		auto bullets = Entity::GameObject::FindObjectsOfType<Bullet>();
		for (auto& bullet : bullets)
		{
			bullet->Destroy();
		}	
	}
}
