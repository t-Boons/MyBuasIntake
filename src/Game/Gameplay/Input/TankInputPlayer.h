// 2022 Tygo Boons

#pragma once

#include "Game/Components.h"
#include "TankInput.h"

// Note the z axis is sideways and x axis is up and down from the current view.

// Macro defines the size in Units of the playfield with the current view.
#define PLAYFIELD_SIZE_Z 25.79f
#define PLAYFIELD_SIZE_X 20.09f

namespace Gameplay
{
	class TankInputPlayer : public TankInput
	{
		IMPLEMENT_COMPONENT_IDENTIFIER_INHERIT(TankInputPlayer, TankInput)

	public:
		virtual void Start() override;
		virtual void UpdateInput() override;

	private:
		RefPtr<Entity::Transform> m_Transform;
	};
}