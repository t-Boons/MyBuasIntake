// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"

namespace Gameplay
{
	class TankManager : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankManager)

	public:

		virtual void Start() override;

		// Set the amount of enemies in the current level.
		void SetEnemyCount(uint32_t count);

		// Called when an enemy tank dies.
		void OnEnemyDie();

		// Called when the player tank dies.
		void OnPlayerDie();

		// Ends the gameplay in the scene
		void EndGameplayInScene();

	private:
		uint32_t m_EnemyCount;

		RefPtr<Entity::AudioSource> m_WinSound;
		RefPtr<Entity::AudioSource> m_LoseSound;
	};
}