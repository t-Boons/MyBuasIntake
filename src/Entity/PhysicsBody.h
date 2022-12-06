// 2022 Tygo Boons

#pragma once

#include "Component.h"
#include "Transform.h"
#include "Physics/AABB.h"

namespace Entity
{
	class PhysicsBody : public Component
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(PhysicsBody)

	public:

	private:
		RefPtr<Transform> m_Transform;

	};
}