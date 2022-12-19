// Tygo Boons 2022

#include "mypch.h"
#include "TankScenePrefabs.h"

namespace Gameplay
{
    std::vector<RefPtr<Entity::GameObject>> TankScenePrefabs::CreateEnviroment()
    {
		// Create vector that has to be filled.
		std::vector<RefPtr<Entity::GameObject>> objects(5);

		// Left collider.
		{
			RefPtr<Entity::GameObject> barrier = Entity::GameObject::Create("LeftBarrier");
			RefPtr<Entity::Transform> transform = barrier->GetComponent<Entity::Transform>();
			auto boxCollider = barrier->AddComponent(Entity::BoxCollider::Create());

			transform->SetScale({ 80, 5, 1 });
			transform->SetPosition({ 0, 1, -22 });

			boxCollider->SetSize(transform->GetScale());

			objects[0] = barrier;
		}

		// Right collider
		{
			RefPtr<Entity::GameObject> barrier = Entity::GameObject::Create("RightBarrier");
			RefPtr<Entity::Transform> transform = barrier->GetComponent<Entity::Transform>();
			auto boxCollider = barrier->AddComponent(Entity::BoxCollider::Create());

			transform->SetScale({ 80, 5, 1 });
			transform->SetPosition({ 0, 1, 21.5f });

			boxCollider->SetSize(transform->GetScale());

			objects[1] = barrier;
		}

		// Bottom collider.
		{
			RefPtr<Entity::GameObject> barrier = Entity::GameObject::Create("BottomBarrier");
			RefPtr<Entity::Transform> transform = barrier->GetComponent<Entity::Transform>();
			auto boxCollider = barrier->AddComponent(Entity::BoxCollider::Create());

			transform->SetScale({ 1, 5, 80 });
			transform->SetPosition({ -14.5f, 1, 0 });

			boxCollider->SetSize(transform->GetScale());

			objects[2] = barrier;
		}

		// Top collider.
		{
			RefPtr<Entity::GameObject> barrier = Entity::GameObject::Create("TopBarrier");
			RefPtr<Entity::Transform> transform = barrier->GetComponent<Entity::Transform>();
			auto boxCollider = barrier->AddComponent(Entity::BoxCollider::Create());

			transform->SetScale({ 1, 5, 80 });
			transform->SetPosition({ 15.25f, 1, 0 });

			boxCollider->SetSize(transform->GetScale());

			objects[3] = barrier;
		}

		{
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

			objects[4] = enviroment;
		}

		return objects;
    }

	RefPtr<Entity::GameObject> TankScenePrefabs::CreateSceneCamera()
	{
		// Create camera object.
		RefPtr<Entity::GameObject> camera = Entity::GameObject::Create("MainCamera");

		RefPtr<Entity::Camera> cam = camera->AddComponent(Entity::Camera::Create());

		// Set view properties, position and rotation to match enviroment.
		cam->SetOrtographicProjection(18.5f, 0.001f, 100.0f);
		cam->SetViewPoint({ -33.5f, 40.0f, -7.2f });
		cam->SetViewRotation({ -45, -90, 0 });

		return camera;
	}

	std::vector<RefPtr<Entity::GameObject>> TankScenePrefabs::CreatePlayerTank(const std::string& name, const glm::vec2& position)
	{
		// Create vector that has to be filled.
		std::vector<RefPtr<Entity::GameObject>> objects(2);

		{
			// Create tank body
			RefPtr<Entity::GameObject> tankBody = Entity::GameObject::Create(name);

			// Set tank position.
			tankBody->GetComponent<Entity::Transform>()->SetPosition({ position.x, 0, position.y });

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

			// Add collision components.
			auto tankCollider = tankBody->AddComponent(Entity::BoxCollider::Create());
			tankCollider->SetSize({ 2, 1, 2 });

			tankBody->AddComponent(Entity::PhysicsBody::Create());


			// Add behavior components.
			tankBody->AddComponent(Gameplay::TankMovement::Create());
			tankBody->AddComponent(Gameplay::TankInput::Create());

			objects[0] = tankBody;
		}

		{
			// Create tank gun.
			RefPtr<Entity::GameObject> tankGun = Entity::GameObject::Create(name + "Gun");

			// Set tank gun position.
			tankGun->GetComponent<Entity::Transform>()->SetPosition({ position.x, 0, position.y });

			auto gunRenderer = tankGun->AddComponent(Entity::MeshRenderer::Create());
			gunRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Tanks/TankGun.obj"));
			gunRenderer->SetMaterial(Renderer::Material::Create(
				Renderer::Texture::Create("Assets/Textures/Tanks/Player/tank_blue.png"),
				Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
			));

			// Add behaviour component.
			tankGun->AddComponent(Gameplay::TankGun::Create());

			objects[1] = tankGun;
		}

		return objects;
	}

	RefPtr<Entity::GameObject> TankScenePrefabs::CreateDebugCamera()
	{
		// Create debug spectator cam.
		RefPtr<Entity::GameObject> flycam = Entity::GameObject::Create("SpectatorCamera");

		flycam->AddComponent(Entity::Camera::Create());
		flycam->AddComponent(Gameplay::FlyingCamera::Create());
		
		return flycam;
	}

	std::vector<RefPtr<Entity::GameObject>> TankScenePrefabs::CreateEnemyTank(const std::string& name, const glm::vec2& position)
	{

		// Create vector that has to be filled.
		std::vector<RefPtr<Entity::GameObject>> objects(2);

		{
			// Create tank body
			RefPtr<Entity::GameObject> tankBody = Entity::GameObject::Create(name);

			// Set tank position.
			tankBody->GetComponent<Entity::Transform>()->SetPosition({ position.x, 0, position.y });

			auto bodyRenderer = tankBody->AddComponent(Entity::MeshRenderer::Create());
			bodyRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Tanks/TankBody.obj"));
			bodyRenderer->SetMaterial(Renderer::Material::Create(
				Renderer::Texture::Create("Assets/Textures/Tanks/Enemy/tank_marin.png"),
				Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
			));

			// Create tank shadow
			auto shadowRenderer = tankBody->AddComponent(Entity::MeshRenderer::Create());
			shadowRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Tanks/TankShadow.obj"));
			shadowRenderer->SetMaterial(Renderer::Material::Create(
				Renderer::Texture::Create("Assets/Textures/Tanks/tank_shadow.png"),
				Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
			));

			// Add collision components.
			auto tankCollider = tankBody->AddComponent(Entity::BoxCollider::Create());
			tankCollider->SetSize({ 2, 1, 2 });

			tankBody->AddComponent(Entity::PhysicsBody::Create());

			objects[0] = tankBody;
		}

		{
			// Create tank gun.
			RefPtr<Entity::GameObject> tankGun = Entity::GameObject::Create(name + "Gun");

			// Set tank gun position.
			tankGun->GetComponent<Entity::Transform>()->SetPosition({ position.x, 0, position.y });

			auto gunRenderer = tankGun->AddComponent(Entity::MeshRenderer::Create());
			gunRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Tanks/TankGun.obj"));
			gunRenderer->SetMaterial(Renderer::Material::Create(
				Renderer::Texture::Create("Assets/Textures/Tanks/Enemy/tank_marin.png"),
				Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
			));

			objects[1] = tankGun;
		}

		return objects;
	}

	RefPtr<Entity::GameObject> TankScenePrefabs::CreateBullet()
	{
		// Create bullet object with uniques name.
		RefPtr<Entity::GameObject> bullet = Entity::GameObject::Create("Bullet" + STR(Core::Time::GetElapsedTime()));

		auto bodyRenderer = bullet->AddComponent(Entity::MeshRenderer::Create());
		bodyRenderer->SetMesh(Renderer::Mesh::Create("Assets/Models/Bullet.obj"));
		bodyRenderer->SetMaterial(Renderer::Material::Create(
			Renderer::Texture::Create("Assets/Textures/Bullet.png"),
			Renderer::Shader::Create("Assets/Shaders/Basic3DShader.glsl")
		));

		auto boxCollider = bullet->AddComponent(Entity::BoxCollider::Create());
		boxCollider->SetSize({ 0.1f, 0.1f, 0.1f });

		bullet->AddComponent(Entity::PhysicsBody::Create());

		bullet->GetComponent<Entity::Transform>()->SetScale({ 0.1f, 0.1f, 0.1f });

		bullet->AddComponent(Bullet::Create());

		return bullet;
	}
}