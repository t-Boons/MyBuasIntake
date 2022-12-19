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

		
			// Create tank body
			RefPtr<Entity::GameObject> cube = Entity::GameObject::Create("Cube");
			cube->GetComponent<Entity::Transform>()->SetScale({ 10, 3, 2 });
			auto bodyRenderer = cube->AddComponent(Entity::MeshRenderer::Create());
			bodyRenderer->SetMesh(Renderer::Mesh::Create("Assets/Cube.obj"));
			bodyRenderer->SetMaterial(Renderer::Material::Create(
				Renderer::Texture::Create("Assets/Textures/Tanks/Player/tank_blue.png"),
				Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
			));


			// Add collision components.
			auto col = cube->AddComponent(Entity::BoxCollider::Create());
			col->SetSize(cube->GetComponent < Entity::Transform>()->GetScale());
		

		AddToScene(cube);
	}
}