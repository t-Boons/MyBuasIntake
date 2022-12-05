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

	private:
		RefPtr<Transform> m_Transform;
		glm::vec3 m_OldPosition;
		Physics::AABB m_BoundingBox;
	};
}