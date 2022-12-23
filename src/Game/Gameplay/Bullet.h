// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/Input/TankInput.h"

#define RICOCHET_AMOUNT 2
#define BULLET_SPEED 7.5f
#define DESTROY_DELAY 0.09f

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
		RefPtr<Entity::AudioSource> m_Clack;
		RefPtr<Entity::AudioSource> m_Thud;
		uint32_t m_Hits;
		float m_DelayTime;
		bool m_DeleteDelayStarted;
	};
}