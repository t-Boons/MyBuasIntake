// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "Game/Gameplay/Input/TankInput.h"

#define MOVEMENT_SPEED 6.0f
#define ROTATION_SPEED 100.0f

#define SPEED_REDUCTION_TIME 0.5f
#define SPEED_REDUCTION_AMOUNT 0.25f

namespace Gameplay
{
	class TankEngine : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankEngine)

	public:
		virtual void Start() override;

		virtual void Update() override;

	private:
		RefPtr<TankInput> m_TankInput;
		RefPtr<Entity::Transform> m_Transform;
		float m_ReduceSpeedTimer;
	};
}