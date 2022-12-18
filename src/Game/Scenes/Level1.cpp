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
		//-------------------//
		// Create cameras.
		//-------------------//

		// Create debug spectator cam.
		RefPtr<Entity::GameObject> flycam = Entity::GameObject::Create("SpectatorCamera");

		flycam->AddComponent(Entity::Camera::Create());
		flycam->AddComponent(Gameplay::FlyingCamera::Create());
		AddToScene(flycam);


		// Create camera object.
		RefPtr<Entity::GameObject> camera = Entity::GameObject::Create("MainCamera");

		RefPtr<Entity::Camera> cam = camera->AddComponent(Entity::Camera::Create());

		cam->SetOrtographicProjection(18.5f, 0.001f, 100.0f);

		cam->SetViewPoint({ -33.5f, 40.0f, -7.2f});
		cam->SetViewRotation({ -45, -90, 0 });

		AddToScene(camera);


		SetActiveCamera(camera->GetComponent<Entity::Camera>());


		//-------------------//
		// Create enviroment.
		//-------------------//

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

		

		//-------------------//
		// Create player tank.
		//-------------------//


		// Create tank body
		RefPtr<Entity::GameObject> tankBody = Entity::GameObject::Create("TankPlayer");

		auto bodyRenderer = tankBody->AddComponent(Entity::MeshRenderer::Create());
		bodyRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Tanks/TankBody.obj"));
		bodyRenderer->SetMaterial(Renderer::Material::Create(
			Renderer::Texture::Create("Assets/Textures/Tanks/Player/tank_blue.png"),
			Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
		));


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
}