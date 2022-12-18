// 2022 Tygo Boons

#include "mypch.h"
#include "Level1.h"
#include "Entity/Components.h"
#include "Game/Gameplay/TankMovement.h"
#include "Game/Gameplay/FlyingCamera.h"
#include "Game/Gameplay/TankGun.h"
#include "Game/Gameplay/TankInput.h"

namespace Gameplay
{
	void Level1::LoadScene()
	{
		CreateSceneCamera();
		CreateEnviroment();
		CreatePlayerTank();
	}

	void Level1::CreateEnviroment()
	{

		// Left collider.
		{
			RefPtr<Entity::GameObject> barrier = Entity::GameObject::Create("LeftBarrier");
			RefPtr<Entity::Transform> transform = barrier->GetComponent<Entity::Transform>();
			auto boxCollider = barrier->AddComponent(Entity::BoxCollider::Create());

			transform->SetScale({ 30, 1, 1 });
			transform->SetPosition({ 0, 1, -22 });

			boxCollider->SetSize(transform->GetScale());

			AddToScene(barrier);
		}

		// Right collider
		{
			RefPtr<Entity::GameObject> barrier = Entity::GameObject::Create("RightBarrier");
			RefPtr<Entity::Transform> transform = barrier->GetComponent<Entity::Transform>();
			auto boxCollider = barrier->AddComponent(Entity::BoxCollider::Create());

			transform->SetScale({ 30, 1, 1 });
			transform->SetPosition({ 0, 1, 21.5f });

			boxCollider->SetSize(transform->GetScale());

			AddToScene(barrier);
		}

		// Bottom collider.
		{
			RefPtr<Entity::GameObject> barrier = Entity::GameObject::Create("BottomBarrier");
			RefPtr<Entity::Transform> transform = barrier->GetComponent<Entity::Transform>();
			auto boxCollider = barrier->AddComponent(Entity::BoxCollider::Create());

			transform->SetScale({ 1, 1, 45 });
			transform->SetPosition({ -14.5f, 1, 0 });

			boxCollider->SetSize(transform->GetScale());

			AddToScene(barrier);
		}

		// Top collider.
		{
			RefPtr<Entity::GameObject> barrier = Entity::GameObject::Create("TopBarrier");
			RefPtr<Entity::Transform> transform = barrier->GetComponent<Entity::Transform>();
			auto boxCollider = barrier->AddComponent(Entity::BoxCollider::Create());

			transform->SetScale({ 1, 1, 45 });
			transform->SetPosition({ 15.25f, 1, 0 });

			boxCollider->SetSize(transform->GetScale());

			AddToScene(barrier);
		}


		// Enviroment mesh.
		RefPtr<Entity::GameObject> enviroment = Entity::GameObject::Create("Enviroment");

		enviroment->AddComponent(Entity::MeshRenderer::Create());
		enviroment->GetComponent<Entity::MeshRenderer>()->SetMesh(Renderer::Mesh::Create("Assets/Models/Enviroment.obj"));
		enviroment->GetComponent<Entity::MeshRenderer>()->SetMaterial(Renderer::Material::Create(
			Renderer::Texture::Create("Assets/Textures/TextureAtlas.png"),
			Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
		));

		// Lower enviroment a little to prevent z-fighting.
		enviroment->GetComponent<Entity::Transform>()->SetPosition({ 0, -0.1f, 0 });

		AddToScene(enviroment);
	}

	void Level1::CreatePlayerTank()
	{

		// Create tank body
		RefPtr<Entity::GameObject> tankBody = Entity::GameObject::Create("TankPlayer");

		auto bodyRenderer = tankBody->AddComponent(Entity::MeshRenderer::Create());
		bodyRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Tanks/TankBody.obj"));
		bodyRenderer->SetMaterial(Renderer::Material::Create(
			Renderer::Texture::Create("Assets/Textures/Tanks/Player/tank_blue.png"),
			Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
		));

		auto tankCollider = tankBody->AddComponent(Entity::BoxCollider::Create());
		tankCollider->SetSize({ 2, 1, 2 });
		tankBody->AddComponent(Entity::PhysicsBody::Create());


		
		// Create tank shadow
		auto shadowRenderer = tankBody->AddComponent(Entity::MeshRenderer::Create());
		shadowRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Tanks/TankShadow.obj"));
		shadowRenderer->SetMaterial(Renderer::Material::Create(
			Renderer::Texture::Create("Assets/Textures/Tanks/tank_shadow.png"),
			Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
		));
			
		tankBody->AddComponent(Gameplay::TankMovement::Create());
		tankBody->AddComponent(Gameplay::TankInput::Create());

		AddToScene(tankBody);
		


		// Create tank gun.
		RefPtr<Entity::GameObject> tankGun = Entity::GameObject::Create("TankPlayerGun");

		auto gunRenderer = tankGun->AddComponent(Entity::MeshRenderer::Create());
		gunRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Tanks/TankGun.obj"));
		gunRenderer->SetMaterial(Renderer::Material::Create(
			Renderer::Texture::Create("Assets/Textures/Tanks/Player/tank_blue.png"),
			Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
		));

		tankGun->AddComponent(Gameplay::TankGun::Create());

		AddToScene(tankGun);

	}

	void Level1::CreateSceneCamera()
	{

		// Create debug spectator cam.
		RefPtr<Entity::GameObject> flycam = Entity::GameObject::Create("SpectatorCamera");

		flycam->AddComponent(Entity::Camera::Create());
		flycam->AddComponent(Gameplay::FlyingCamera::Create());
		AddToScene(flycam);


		// Create camera object.
		RefPtr<Entity::GameObject> camera = Entity::GameObject::Create("MainCamera");

		RefPtr<Entity::Camera> cam = camera->AddComponent(Entity::Camera::Create());

		cam->SetOrtographicProjection(18.5f, 0.001f, 100.0f);

		cam->SetViewPoint({ -33.5f, 40.0f, -7.2f });
		cam->SetViewRotation({ -45, -90, 0 });

		AddToScene(camera);

		// Set active camera the scene is rendered from.
		SetActiveCamera(camera->GetComponent<Entity::Camera>());
	}
}