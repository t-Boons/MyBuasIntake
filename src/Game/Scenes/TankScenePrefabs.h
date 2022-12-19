// Tygo Boons

#pragma once

#include "Entity/Components.h"
#include "Game/Gameplay/TankMovement.h"
#include "Game/Gameplay/FlyingCamera.h"
#include "Game/Gameplay/TankGun.h"
#include "Game/Gameplay/TankInput.h"

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
		static std::vector<RefPtr<Entity::GameObject>> CreatePlayerTank();

		// Get Spectator camera gameobject instance.
		static RefPtr<Entity::GameObject> CreateDebugCamera();
	};
}