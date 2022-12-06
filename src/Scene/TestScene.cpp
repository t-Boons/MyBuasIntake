// 2022 Tygo Boons

#include "mypch.h"
#include "TestScene.h"
#include "Entity/GameObject.h"
#include "Entity/MeshRenderer.h"
#include "Gameplay/TankMovement.h"
#include "Entity/Camera.h"
#include "Gameplay/FlyingCamera.h"
#include "Entity/BoxCollider.h"
#include "Gameplay/TestBehaviour.h"
#include "Entity/PhysicsBody.h"

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

		auto cam = flyCam->AddComponent(Entity::Camera::Create());

		SetActiveCamera(flyCam->GetComponent<Entity::Camera>());

		AddToScene(flyCam);
		//AddToScene(tank);




		
		RefPtr<Entity::GameObject> cube0 = Entity::GameObject::Create("Cube0");
		{
			cube0->AddComponent(Entity::BoxCollider::Create());
			cube0->AddComponent(Gameplay::TestBehaviour::Create());

			auto meshr = cube0->AddComponent(Entity::MeshRenderer::Create());
			meshr->SetMesh(Renderer::Mesh::Create("assets/Cube.obj"));
			meshr->SetMaterial(Renderer::Material::Create(tex, shader));

			cube0->AddComponent(Entity::PhysicsBody::Create());
		}

		RefPtr<Entity::GameObject> cube1 = Entity::GameObject::Create("Cube1");
		{
			cube1->AddComponent(Entity::BoxCollider::Create());
			auto meshr = cube1->AddComponent(Entity::MeshRenderer::Create());
			meshr->SetMesh(Renderer::Mesh::Create("assets/Cube.obj"));
			meshr->SetMaterial(Renderer::Material::Create(tex, shader));

			cube1->GetComponent<Entity::Transform>()->Translate({ 0, -10, 0 });
			cube1->GetComponent<Entity::Transform>()->SetScale({ 10, 1, 10 });
		}


		AddToScene(cube0);
		AddToScene(cube1);
	}
}