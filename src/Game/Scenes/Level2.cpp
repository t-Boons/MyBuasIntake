// 2023 Tygo Boons

#include "mypch.h"
#include "Level2.h"
#include "ScenePrefabs.h"
#include "Game/Components.h"
#include "Game/Gameplay/TankGameSettings.h"

namespace Gameplay
{
	void Level2::LoadScene()
	{
		// Add camera to scene.
		auto camera = USE_SPECTATOR_CAMERA ? ScenePrefabs::CreateSpectatorCamera() : ScenePrefabs::CreateSceneCamera();
		AddToScene(camera);
		SetActiveCamera(camera->GetComponent<Entity::Camera>());

		// Add Enviroment to scene.
		AddToScene(ScenePrefabs::CreateEnviroment());

		// Add player tank to scene.
		AddToScene(ScenePrefabs::CreatePlayerTank({ -10, -15}));


		auto enemyTank = ScenePrefabs::CreateAshEnemyTank({ 10, 15 });

		// Get the enemy tank gun component and make the barrel point the -1, 0 direction.
		enemyTank[0]->GetComponent<TankInputAshEnemy>()->SetInitialGunRotation({ -1, 0 });

		AddToScene(enemyTank);
		

		///   Load obstacles in middle
		// ----------------------------------
		// |								|
		// |	  [               ]		    |
		// |	    						|
		// |								|
		// |	    [               ]		|
		// |								|
		// |								|
		// ----------------------------------

		// Top
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -14 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -12 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -10 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -8 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -6 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -4 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -2 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -0 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, 2 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, 4 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, 6 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, 8 }));

		// Bottom
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -10 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -8 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -6 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -4 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -2 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -0 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, 2 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, 4 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, 6 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, 8 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, 10 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, 12 }));

		AddToScene(ScenePrefabs::CreateCollider({ -6, 1 }, { 2, 24 }));
		AddToScene(ScenePrefabs::CreateCollider({ 6, -3 }, { 2, 24 }));

		// Create tank manager that keeps track of all enemy tanks.
		AddToScene(ScenePrefabs::CreateTankManager(1));

		AddToScene(ScenePrefabs::CreateMusic("Assets/Audio/Music/Tanks_Variation_2.ogg"));
	}
}