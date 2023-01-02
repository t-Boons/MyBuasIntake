// 2022 Tygo Boons

#include "mypch.h"
#include "Level1.h"
#include "ScenePrefabs.h"
#include "Game/Components.h"

namespace Gameplay
{
	void Level1::LoadScene()
	{
		// Initializes tank scene prefab class.
		ScenePrefabs::Initialize();

		// Add camera to scene.
		auto camera = USE_SPECTATOR_CAMERA ? ScenePrefabs::CreateSpectatorCamera() : ScenePrefabs::CreateSceneCamera();
		AddToScene(camera);
		SetActiveCamera(camera->GetComponent<Entity::Camera>());

		// Add Enviroment to scene.
		AddToScene(ScenePrefabs::CreateEnviroment());

		// Add player tank to scene.
		AddToScene(ScenePrefabs::CreatePlayerTank({ 0, -15}));

		AddToScene(ScenePrefabs::CreateBrownEnemyTank({ 0, 10 }));


		///   Load obstacles on the left.
		// ----------------------------------
		// |								|
		// |	 [ ]						|
		// |	 [ ]						|
		// |								|
		// |	 [ ]						|
		// |	 [ ]						|
		// |								|
		// ----------------------------------

		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -10 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -4, -10 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 4, -10 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -10 }));

		AddToScene(ScenePrefabs::CreateCollider({ -5, -10 }, { 4, 2 }));
		AddToScene(ScenePrefabs::CreateCollider({ 5, -10 }, { 4, 2 }));

		///    Load obstacle in the middle.
		// ----------------------------------
		// |								|
		// |	 		 [ ]				|
		// |	 		 [ ]				|
		// |			 [ ]				|
		// |	 		 [ ]				|
		// |	 		 [ ]				|
		// |								|
		// ----------------------------------
		
		AddToScene(ScenePrefabs::CreateBlockMesh({ -6, -0 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -4, -0 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -2, -0 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ -0, -0 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 2, -0 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 4, -0 }));
		AddToScene(ScenePrefabs::CreateBlockMesh({ 6, -0 }));

		AddToScene(ScenePrefabs::CreateCollider({ 0, 0 }, { 14, 2 }));

		// Create tank manager that keeps track of all enemy tanks.
		AddToScene(ScenePrefabs::CreateTankManager(1));


		RefPtr<Entity::GameObject> mainTheme = Entity::GameObject::Create("Speaker");
		auto aud = mainTheme->AddComponent(Entity::AudioSource::Create());
		aud->LoadClipFromFile("Assets/Audio/Music/Tanks_Variation_1.ogg");
		aud->SetLooping(true);
		aud->Play();

		AddToScene(mainTheme);
	}
}