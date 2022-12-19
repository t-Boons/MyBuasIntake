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

		// Set the size of the AABB.
		void SetSize(const glm::vec3& size) { m_Size = size; }

		// See if this collider intersects with another colilder.
		RefPtr<Physics::Collision> Intersects(const RefPtr<BoxCollider>& collider);

		// Update the last valid position outside of any colliders.
		void UpdateLastValidPosition();

		// Get direction normal.
		glm::vec3 GetNormalFromLastValidPosition() const;

		// Reset to the last valid position.
		void ResetToLastValidPosition();

		// See if the last valid position is not infinity
		bool IsInitialized() const { return m_LastValidPosition != glm::vec3(INFINITE); }

	private:
		glm::vec3 m_LastValidPosition = glm::vec3(INFINITE);
		glm::vec3 m_DirectionNormal = glm::vec3(0.0f);
		glm::vec3 m_Size = { 1, 1, 1 };
		RefPtr<Transform> m_Transform;
		Physics::AABB m_BoundingBox;
	};
}