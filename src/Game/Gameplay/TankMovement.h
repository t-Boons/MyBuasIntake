// 2022 Tygo Boons

#pragma once

#include "Core/Core.h"
#include "Entity/Components.h"

namespace Gameplay
{
	class TankMovement : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankMovement)

	public:
		virtual void Start() override;

		virtual void Update() override;

	private:
		RefPtr<Entity::Transform> m_Transform;
	};
}