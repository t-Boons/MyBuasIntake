// 2022 Tygo Boons

#include "mypch.h"
#include "Level1.h"
#include "TankScenePrefabs.h"
#include "Entity/Components.h"


namespace Gameplay
{
	void Level1::LoadScene()
	{
		bool useSpectatorCamera = false;

		// Add camera to scene.
		auto camera = useSpectatorCamera ? TankScenePrefabs::CreateDebugCamera() : TankScenePrefabs::CreateSceneCamera();
		AddToScene(camera);
		SetActiveCamera(camera->GetComponent<Entity::Camera>());

		// Add Enviroment to scene.
		AddToScene(TankScenePrefabs::CreateEnviroment());

		// Add player tank to scene.
		AddToScene(TankScenePrefabs::CreatePlayerTank("PlayerTank", {-10, 5}));

		AddToScene(TankScenePrefabs::CreateEnemyTank("EnemyTank", { 3, 9 }));
	}
}