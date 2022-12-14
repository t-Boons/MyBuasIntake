// 2022 Tygo Boons

#pragma once

#include "ScriptComponent.h"
#include "Core/Core.h"
#include "Entity/Components.h"
#include "Core/Time.h"

namespace Gameplay
{
	class TankGun : public ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankGun)

	public:
		virtual void Start() override;

		virtual void Update() override;

	private:
		RefPtr<Entity::Transform> m_ParentTransform;
		RefPtr<Entity::Transform> m_Transform;
	};
}