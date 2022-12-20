// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/TankInput.h"

#define RICOCHET_AMOUNT 20
#define BULLET_SPEED 100.0f

namespace Gameplay
{
	class Bullet : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(Bullet)

	public:
		virtual void Start() override;

		virtual void Update() override;

		virtual void OnCollisionEnter(RefPtr<Physics::Collision> collision) override;

	private:
		RefPtr<Entity::Transform> m_Transform;
		uint32_t m_Hits;
	};
}