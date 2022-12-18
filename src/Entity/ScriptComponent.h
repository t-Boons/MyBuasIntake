// 2022 Tygo Boons

#pragma once

#include "Entity/Component.h"

namespace Entity
{
	class ScriptComponent : public Entity::Component
	{
	public:

		// Runs when object is colliding with another object.
		virtual void OnCollisionEnter(RefPtr<Physics::Collision> collision) {}
	};
}