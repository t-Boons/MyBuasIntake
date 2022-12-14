// 2022 Tygo Boons

#pragma once

#include "Core/Core.h"
#include "Entity/Components.h"

namespace Gameplay
{
	class TestBehaviour : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TestBehaviour)

	public:
		virtual void Start() override;

		virtual void Update() override;
		virtual void OnCollisionEnter(RefPtr<Physics::Collision> collision) override;

	public:
		RefPtr<Entity::Transform> m_Transform;
		float m_Gravity = 0.5f;
		float m_FallSpeed = 0;
	};
}