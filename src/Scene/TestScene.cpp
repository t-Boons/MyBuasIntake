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
		// Create camera object.
		RefPtr<Entity::GameObject> camera = Entity::GameObject::Create("MainCamera");

		RefPtr<Entity::Camera> cam = camera->AddComponent(Entity::Camera::Create());

		cam->SetOrtographicProjection(19, 0.01f, 100.0f);

		cam->SetViewPoint({ -8.537f, 19.27f, -7.12f });
		cam->SetViewRotation({ -55, -90, 0 });

		AddToScene(camera);

		SetActiveCamera(cam);


		// Create enviroment.
		RefPtr<Entity::GameObject> enviroment = Entity::GameObject::Create("BasePlate");

		enviroment->AddComponent(Entity::MeshRenderer::Create());
		enviroment->GetComponent<Entity::MeshRenderer>()->SetMesh(Renderer::Mesh::Create("assets/Models/Enviroment.obj"));
		enviroment->GetComponent<Entity::MeshRenderer>()->SetMaterial(Renderer::Material::Create(
																		Renderer::Texture::Create("assets/Models/TextureAtlas.png"),
																		Renderer::Shader::Create("assets/Shaders/Basic3DShader.glsl")
																	));

		AddToScene(enviroment);

			
	}
}