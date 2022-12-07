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

		// Reset to the last valid position.
		void ResetToLastValidPosition();

	private:
		void UpdateScaleAndPosition();

	public:
		glm::vec3 m_LastValidPosition;

	private:
		bool m_Intersects;
		RefPtr<Transform> m_Transform;
		Physics::AABB m_BoundingBox;
	};
}