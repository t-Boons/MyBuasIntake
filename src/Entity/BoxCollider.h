// 2022 Tygo Boons

#pragma once

#include "Component.h"
#include "Transform.h"
#include "Physics/AABB.h"

namespace Entity
{

	class BoxCollider : public Component
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(BoxCollider)

	public:

		virtual void Start() override;
		virtual void Update() override;

		// See if this collider intersects with another colilder.
		bool Intersects(const RefPtr<BoxCollider>& collider) { return m_BoundingBox.Intersects(collider->m_BoundingBox); }

		// Update the last valid position outside of any colliders.
		void UpdateLastValidPosition();

		// Get direction normal.
		glm::vec3 GetNormalFromLastValidPosition() const;

		// Reset to the last valid position.
		void ResetToLastValidPosition();


	private:
		glm::vec3 m_LastValidPosition;
		glm::vec3 m_DirectionNormal;
		RefPtr<Transform> m_Transform;
		Physics::AABB m_BoundingBox;
	};
}