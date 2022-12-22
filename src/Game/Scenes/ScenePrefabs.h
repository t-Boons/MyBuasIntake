// Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/TankMovement.h"
#include "Game/Gameplay/FlyingCamera.h"
#include "Game/Gameplay/TankGun.h"
#include "Game/Gameplay/Input/TankInputPlayer.h"
#include "Game/Gameplay/Input/TankInputBrownEnemy.h"
#include "Game/Gameplay/Bullet.h"

namespace Gameplay
{
	class ScenePrefabs
	{
	public:

		// Initializes the default variables.
		static void Initialize();

		// Get Enviroment gameobject(s) instance.
		static std::vector<RefPtr<Entity::GameObject>> CreateEnviroment();

		// Get Scene Camera gameobject instance.
		static RefPtr<Entity::GameObject> CreateSceneCamera();

		// Get Player Tank gameobject(s) instance.
		static std::vector<RefPtr<Entity::GameObject>> CreatePlayerTank(const glm::vec2& position);

		// Get Spectator camera gameobject instance.
		static RefPtr<Entity::GameObject> CreateDebugCamera();

		// Get Enemy tank gameobject(s) instance.
		static std::vector<RefPtr<Entity::GameObject>> CreateEnemyTank(const glm::vec2& position);

		// Get Bullet gameobject instance.
		static RefPtr<Entity::GameObject> CreateBullet();

		// Get Block gameobject instance.
		static RefPtr<Entity::GameObject> CreateBlockMesh(const glm::vec2& position);

		// Get collider instance
		static RefPtr<Entity::GameObject> CreateCollider(const glm::vec2& position, const glm::vec2& scale);

		static RefPtr<Renderer::Shader> s_Basic3DShader;
		static RefPtr<Renderer::Texture> s_TextureAtlasTexture;
		static RefPtr<Renderer::Material> s_TextureAtlasMaterial;
	};
}