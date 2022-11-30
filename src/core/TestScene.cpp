// 2022 Tygo Boons

#include "TestScene.h"
#include "Entity/GameObject.h"
#include "Entity/MeshRenderer.h"

namespace Core
{
	void TestScene::LoadScene()
	{
		// Load Tank.
		RefPtr<Entity::GameObject> tank = std::make_shared<Entity::GameObject>("Hi");
		tank->AddComponent<Entity::MeshRenderer>(std::make_shared<Entity::MeshRenderer>());
		
		tank->GetComponent<Entity::MeshRenderer>()->SetMesh(Renderer::Mesh::Create("assets/Tanks/TankPlayer.obj"));

		RefPtr<Renderer::Texture> tex = Renderer::Texture::Create("assets/Tanks/textures/enemy/tank_marin.png");
		RefPtr<Renderer::Shader> shader = Renderer::Shader::Create("assets/shaders/Basic3DShader.glsl");
		RefPtr<Renderer::Material> material = Renderer::Material::Create(tex, shader);

		tank->GetComponent<Entity::MeshRenderer>()->SetMaterial(material);


		AddToScene(tank);
	}

}