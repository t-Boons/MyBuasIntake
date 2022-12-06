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

		// Try to see if this object collides with collide rand fix the transform if it does.
		void TryCollision(const RefPtr<BoxCollider>& collider);

		// See if this collider intersects with another colilder.
		bool Intersects(const RefPtr<BoxCollider>& collider) { return m_BoundingBox.Intersects(collider->m_BoundingBox); }

	private:
		RefPtr<Transform> m_Transform;
		glm::vec3 m_LastValidPosition;
		Physics::AABB m_BoundingBox;
	};
}