// 2022 Tygo Boons

#pragma once

#include "ScriptComponent.h"
#include "Core/Core.h"
#include "Entity/Transform.h"

namespace Gameplay
{
	class TestBehaviour : public ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TestBehaviour)

	public:
		virtual void Start() override;

		virtual void Update() override;

	public:
		RefPtr<Entity::Transform> m_Transform;
		float m_Gravity = 0.5f;
		float m_FallSpeed = 0;
	};
}