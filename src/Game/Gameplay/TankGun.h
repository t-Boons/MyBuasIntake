// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/TankInput.h"
#include "Game/Scenes/ScenePrefabs.h"

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

		// See if the gun has ammo. reload if it doesnt..
		bool HasAmmo();

		// Reload the gun.
		void Reload();

		// Set the parent object the gun will be parented to.
		void SetTankParent(const RefPtr<Entity::Transform>& parent) { m_ParentTransform = parent; }

	private:
		RefPtr<Entity::GameObject> m_BulletPrefab;

		RefPtr<Entity::Transform> m_ParentTransform;
		RefPtr<Entity::Transform> m_Transform;
		RefPtr<TankInput> m_Input;

		std::thread m_RefilBulletThread;
		std::atomic<bool> m_Reloaded;
		std::atomic<uint32_t> m_BulletsInChamber;
	};
}