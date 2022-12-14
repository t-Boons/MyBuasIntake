// 2022 Tygo Boons

#pragma once

#include "Entity/Component.h"

namespace Entity
{
	class ScriptComponent : public Entity::Component
	{
	public:

		// Get component of this gameobject.
		template<class T>
		const RefPtr<T> GetComponent()
		{
			return Parent->GetComponent<T>();
		}

		// Add Component to this gameobject.
		template<class T>
		const RefPtr<T> AddComponent()
		{
			return Parent->AddComponent<T>();
		}

		// Runs when object is colliding with another object.
		virtual void OnCollisionEnter(RefPtr<Physics::Collision> collision) {}
	};
}