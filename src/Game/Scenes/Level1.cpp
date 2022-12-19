// 2022 Tygo Boons

#include "mypch.h"
#include "Level1.h"
#include "TankScenePrefabs.h"
#include "Entity/Components.h"
#include "Game/Gameplay/TankMovement.h"
#include "Game/Gameplay/FlyingCamera.h"
#include "Game/Gameplay/TankGun.h"
#include "Game/Gameplay/TankInput.h"



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
		AddToScene(TankScenePrefabs::CreatePlayerTank());
	}
}