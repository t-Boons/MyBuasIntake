// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/TankGun.h"
#include "Game/Gameplay/Input/TankInput.h"

#define MOVEMENT_SPEED 6.0f
#define ROTATION_SPEED 100.0f

#define SPEED_REDUCTION_TIME 0.35f
#define SPEED_REDUCTION_AMOUNT 0.25f

namespace Gameplay
{
	class TankGun;

	class TankEngine : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankEngine)

	public:
		virtual void Start() override;

		virtual void Update() override;

		virtual void OnCollisionEnter(RefPtr<Physics::Collision> collision) override;

		// Sets the gun object to the gun of this tank.
		void SetGunObject(const RefPtr<Gameplay::TankGun>& gun) { m_TankGun = gun; }

	private:
		RefPtr<Gameplay::TankGun> m_TankGun;

		RefPtr<TankInput> m_TankInput;
		RefPtr<Entity::Transform> m_Transform;
		RefPtr<Entity::AudioSource> m_ExplosionSound;
		float m_ReduceSpeedTimer;
		bool m_IsDead;
	};
}