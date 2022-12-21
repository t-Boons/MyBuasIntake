// 2022 Tygo Boons

#include "mypch.h"
#include "Level1.h"
#include "TankScenePrefabs.h"
#include "Game/Components.h"


namespace Gameplay
{
	void Level1::LoadScene()
	{
		// Initializes tank scene prefab class
		TankScenePrefabs::Initialize();

		bool useSpectatorCamera = false;

		// Add camera to scene.
		auto camera = useSpectatorCamera ? TankScenePrefabs::CreateDebugCamera() : TankScenePrefabs::CreateSceneCamera();
		AddToScene(camera);
		SetActiveCamera(camera->GetComponent<Entity::Camera>());

		// Add Enviroment to scene.
		AddToScene(TankScenePrefabs::CreateEnviroment());

		// Add player tank to scene.
		AddToScene(TankScenePrefabs::CreatePlayerTank("PlayerTank", { 0, -15}));

		AddToScene(TankScenePrefabs::CreateEnemyTank("EnemyTank", { 0, 10 }));
		

		// Load obstacle on the left.
		// ----------------------------------
		// |								|
		// |	 [ ]						|
		// |	 [ ]						|
		// |								|
		// |	 [ ]						|
		// |	 [ ]						|
		// |								|
		// ----------------------------------

		AddToScene(TankScenePrefabs::CreateBlockMesh({ -6, -10 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ -4, -10 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ 4, -10 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ 6, -10 }));

		AddToScene(TankScenePrefabs::CreateCollider({ -5, -10 }, { 4, 2}));
		AddToScene(TankScenePrefabs::CreateCollider({ 5, -10	 }, { 4, 2 }));


		// Load obstacle in the middle.
		// ----------------------------------
		// |								|
		// |	 		 [ ]				|
		// |	 		 [ ]				|
		// |			 [ ]				|
		// |	 		 [ ]				|
		// |	 		 [ ]				|
		// |								|
		// ----------------------------------

		AddToScene(TankScenePrefabs::CreateBlockMesh({ -6, -0 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ -4, -0 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ -2, -0 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ -0, -0 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ 2, -0 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ 4, -0 }));
		AddToScene(TankScenePrefabs::CreateBlockMesh({ 6, -0 }));

		AddToScene(TankScenePrefabs::CreateCollider({ 0, 0 }, { 14, 2 }));
	}
}