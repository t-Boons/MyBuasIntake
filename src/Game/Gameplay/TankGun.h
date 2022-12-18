// 2022 Tygo Boons

#pragma once

#include "Core/Core.h"
#include "Entity/Components.h"
#include "Core/Time.h"


// Note the z axis is sideways and x axis is up and down from the current view.

// Macro defines the size in Units of the playfield with the current view.
#define PLAYFIELD_SIZE_Z 25.79f
#define PLAYFIELD_SIZE_X 20.09f

namespace Gameplay
{
	class TankGun : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankGun)

	public:
		virtual void Start() override;

		virtual void Update() override;

		void SetGunRotation(const glm::vec2& direction);

		// Returns the tank position from word space units to screen space units.
		glm::vec2 GetNormalizedTankPosition() const;

	private:
		RefPtr<Entity::Transform> m_ParentTransform;
		RefPtr<Entity::Transform> m_Transform;
	};
}