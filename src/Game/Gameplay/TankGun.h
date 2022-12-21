// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/TankInput.h"

#define CONSECUTIVE_BULLET_COUNT 3;
#define BULLET_REFIL_DELAY 2000

namespace Gameplay
{

	class TankGun : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankGun)

	public:
		virtual void Start() override;

		virtual void Update() override;

		// Set the rotation of the tank gun.
		void SetGunRotation(const glm::vec2& direction);

		// Shoots a bullet in the gun's direction.
		void Shoot();

		// Reloads the gun if it is not already reloading.
		void Reload();

	private:
		RefPtr<Entity::Transform> m_ParentTransform;
		RefPtr<Entity::Transform> m_Transform;
		RefPtr<TankInput> m_Input;
		std::thread m_RefilBulletThread;
		std::atomic<bool> m_Reloaded;
		std::atomic<uint32_t> m_BulletReadyToFireCount;
	};
}