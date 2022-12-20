// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/TankInput.h"

namespace Gameplay
{
	class TankMovement : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankMovement)

	public:
		virtual void Start() override;

		virtual void Update() override;

	private:
		RefPtr<TankInput> m_TankInput;
		RefPtr<Entity::Transform> m_Transform;
	};
}