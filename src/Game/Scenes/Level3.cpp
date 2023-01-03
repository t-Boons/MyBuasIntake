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


		auto enemyTank = ScenePrefabs::CreateAshEnemyTank({ 10, 15 });

		// Get the enemy tank gun component and make the barrel point the -1, 0 direction.
		enemyTank[0]->GetComponent<TankInputAshEnemy>()->SetInitialGunRotation({ -1, 0 });

		AddToScene(enemyTank);
		


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


		// Create tank manager that keeps track of all enemy tanks.
		AddToScene(ScenePrefabs::CreateTankManager(3));

		AddToScene(ScenePrefabs::CreateMusic("Assets/Audio/Music/Tanks_Variation_3.ogg"));
	}
}