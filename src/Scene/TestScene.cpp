// 2022 Tygo Boons

#include "mypch.h"
#include "TestScene.h"
#include "Entity/GameObject.h"
#include "Entity/MeshRenderer.h"
#include "Gameplay/TankMovement.h"
#include "Entity/Camera.h"
#include "Gameplay/FlyingCamera.h"

namespace Core
{
	void TestScene::LoadScene()
	{
		// Load Tank.
		RefPtr<Entity::GameObject> tank = Entity::GameObject::Create("Tank");

		tank->AddComponent(Entity::MeshRenderer::Create());
		tank->GetComponent<Entity::MeshRenderer>()->SetMesh(Renderer::Mesh::Create("assets/Tanks/TankPlayer.obj"));

		RefPtr<Renderer::Texture> tex = Renderer::Texture::Create("assets/Tanks/textures/enemy/tank_marin.png");
		RefPtr<Renderer::Shader> shader = Renderer::Shader::Create("assets/shaders/Basic3DShader.glsl");
		RefPtr<Renderer::Material> material = Renderer::Material::Create(tex, shader);

		tank->GetComponent<Entity::MeshRenderer>()->SetMaterial(material);

		tank->AddComponent(Gameplay::TankMovement::Create());

		RefPtr<Entity::GameObject> flyCam = Entity::GameObject::Create("Spectator Camera");
		flyCam->AddComponent(Gameplay::FlyingCamera::Create());

		flyCam->AddComponent(Entity::Camera::Create());

		SetActiveCamera(flyCam->GetComponent<Entity::Camera>());

		AddToScene(flyCam);
		AddToScene(tank);
	}
}