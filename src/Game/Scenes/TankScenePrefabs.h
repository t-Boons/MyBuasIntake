// Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/TankMovement.h"
#include "Game/Gameplay/FlyingCamera.h"
#include "Game/Gameplay/TankGun.h"
#include "Game/Gameplay/TankInput.h"
#include "Game/Gameplay/Bullet.h"

namespace Gameplay
{
	class TankScenePrefabs
	{
	public:

		// Get Enviroment gameobject(s) instance.
		static std::vector<RefPtr<Entity::GameObject>> CreateEnviroment();

		// Get Scene Camera gameobject instance.
		static RefPtr<Entity::GameObject> CreateSceneCamera();

		// Get Player Tank gameobject(s) instance.
		static std::vector<RefPtr<Entity::GameObject>> CreatePlayerTank(const std::string& name, const glm::vec2& position);

		// Get Spectator camera gameobject instance.
		static RefPtr<Entity::GameObject> CreateDebugCamera();

		// Get Enemy tank gameobject(s) instance.
		static std::vector<RefPtr<Entity::GameObject>> CreateEnemyTank(const std::string& name, const glm::vec2& position);

		// Get Bullet gameobject instance.
		static RefPtr<Entity::GameObject> CreateBullet();
	};
}