// 2023 Tygo Boons

#include "mypch.h"
#include "Level3.h"
#include "ScenePrefabs.h"
#include "Game/Components.h"
#include "Game/Gameplay/TankGameSettings.h"

namespace Gameplay
{
	void Level3::LoadScene()
	{
		ScenePrefabs::Initialize();


		// Add camera to scene.
		auto camera = USE_SPECTATOR_CAMERA ? ScenePrefabs::CreateSpectatorCamera() : ScenePrefabs::CreateSceneCamera();
		AddToScene(camera);
		SetActiveCamera(camera->GetComponent<Entity::Camera>());

		// Add Enviroment to scene.
		AddToScene(ScenePrefabs::CreateEnviroment());

		// Add player tank to scene.
		AddToScene(ScenePrefabs::CreatePlayerTank({ -10, -15}));


		/// Create all 3 enemy tanks.
		// Bottom right tank.
		{
			auto enemyTank = ScenePrefabs::CreateAshEnemyTank({ -12, 15 });

			// Get the enemy tank gun component and make the barrel point the -1, 0 direction.
			enemyTank[0]->GetComponent<TankInputAshEnemy>()->SetInitialGunRotation({ 0, 1 });

			AddToScene(enemyTank);
		}
		// Top left tank.
		{
			auto enemyTank = ScenePrefabs::CreateAshEnemyTank({ 12, -15 });

			// Get the enemy tank gun component and make the barrel point the -1, 0 direction.
			enemyTank[0]->GetComponent<TankInputAshEnemy>()->SetInitialGunRotation({ 0, -1 });

			AddToScene(enemyTank);
		}
		// Left tank.
		{
			auto enemyTank = ScenePrefabs::CreateBrownEnemyTank({ 0, 17 });

			// Get the enemy tank gun component and make the barrel point the -1, 0 direction.
			enemyTank[0]->GetComponent<TankInputBrownEnemy>()->SetInitialGunRotation({ -1, 0 });

			AddToScene(enemyTank);
		}



		///   Load obstacle on top.
		// ----------------------------------
		// |								|
		// |	  [         ]		        |
		// |	    						|
		// |								|
		// |								|
		// |								|
		// |								|
		// ----------------------------------

		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, -15 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, -13 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, -11 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, -9 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, -7 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, -5 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, -3 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, -1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 8, 1 }));

		AddToScene(ScenePrefabs::CreateCollider({ 8, -7 }, { 2, 18 }));

		///   Load obstacle in middle.
		// ----------------------------------
		// |								|
		// |			   []		        |
		// |	    	   []				|
		// |			 [][]				|
		// |			 []					|
		// |			 []					|
		// |								|
		// ----------------------------------

		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, 1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 4, 1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 2, 1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 0, 1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 0, -1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -2, -1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -4, -1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -1 }));

		AddToScene(ScenePrefabs::CreateCollider({ 3, 1 }, { 8, 2 }));
		AddToScene(ScenePrefabs::CreateCollider({ -4, -1 }, { 10, 2 }));

		///   Load obstacle on top.
		// ----------------------------------
		// |								|
		// |	    						|
		// |								|
		// |								|
		// |								|
		// |			  [         ]		|
		// |								|
		// ----------------------------------

		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, 15 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, 13 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, 11 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, 9 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, 7 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, 5 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, 3 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, 1 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -8, -1 }));

		AddToScene(ScenePrefabs::CreateCollider({ -8, 7 }, { 2, 18 }));



		// Create tank manager that keeps track of all enemy tanks.
		AddToScene(ScenePrefabs::CreateTankManager(3));

		AddToScene(ScenePrefabs::CreateMusic("Assets/Audio/Music/Tanks_Variation_3.ogg"));
	}
}