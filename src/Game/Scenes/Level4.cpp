// 2023 Tygo Boons

#include "mypch.h"
#include "Level4.h"
#include "ScenePrefabs.h"
#include "Game/Components.h"
#include "Game/Gameplay/TankGameSettings.h"

namespace Gameplay
{
	void Level4::LoadScene()
	{
		ScenePrefabs::Initialize();


		// Add camera to scene.
		auto camera = USE_SPECTATOR_CAMERA ? ScenePrefabs::CreateSpectatorCamera() : ScenePrefabs::CreateSceneCamera();
		AddToScene(camera);
		SetActiveCamera(camera->GetComponent<Entity::Camera>());

		// Add Enviroment to scene.
		AddToScene(ScenePrefabs::CreateEnviroment());

		// Add player tank to scene.
		AddToScene(ScenePrefabs::CreatePlayerTank({ -6, -15 }));


		/// Create all 3 enemy tanks.
		// Top right tank.
		{
			auto enemyTank = ScenePrefabs::CreateAshEnemyTank({ 10, 15 });

			// Get the enemy tank gun component and make the barrel point the -1, 0 direction.
			enemyTank[0]->GetComponent<TankInputAshEnemy>()->SetInitialGunRotation({ -1, -1 });

			AddToScene(enemyTank);
		}
		// Middle right
		{
			auto enemyTank = ScenePrefabs::CreateBrownEnemyTank({ 0, 16 });

			// Get the enemy tank gun component and make the barrel point the -1, 0 direction.
			enemyTank[0]->GetComponent<TankInputBrownEnemy>()->SetInitialGunRotation({ -1, 0 });

			AddToScene(enemyTank);
		}
		// Middle top
		{
			auto enemyTank = ScenePrefabs::CreateBrownEnemyTank({ 11, 5 });

			// Get the enemy tank gun component and make the barrel point the -1, 0 direction.
			enemyTank[0]->GetComponent<TankInputBrownEnemy>()->SetInitialGunRotation({ -0.1f, -1 });

			AddToScene(enemyTank);
		}

		// Create tank manager that keeps track of all enemy tanks.
		AddToScene(ScenePrefabs::CreateTankManager(3));

		AddToScene(ScenePrefabs::CreateMusic("Assets/Audio/Music/Tanks_Variation_3.ogg"));
	}
}