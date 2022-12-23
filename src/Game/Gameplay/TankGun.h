// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/Input/TankInput.h"
#include "Game/Scenes/ScenePrefabs.h"

#define CONSECUTIVE_BULLET_COUNT 5
#define BULLET_REFIL_DELAY 2.75f

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

		// Returns if the gun has been fired this frame.
		bool IsShooting() const { return m_IsShooting; }

	private:
		RefPtr<Entity::GameObject> m_BulletPrefab;

		RefPtr<Entity::Transform> m_ParentTransform;
		RefPtr<Entity::Transform> m_Transform;
		RefPtr<Entity::AudioSource> m_GunShot;

		RefPtr<TankInput> m_Input;

		uint32_t m_BulletsInChamber; 
		bool m_Reloaded, m_IsShooting;
	};
}