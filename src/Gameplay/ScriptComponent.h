// 2022 Tygo Boons

#pragma once
#include "Entity/Component.h"

namespace Gameplay
{
	class ScriptComponent : public Entity::Component
	{
	public:

		// GetComponent abstraction.
		template<class T>
		const RefPtr<T> GetComponent()
		{
			return Parent->GetComponent<T>();
		}

		// AddComponent abstraction for GameObject.
		template<class T>
		const RefPtr<T> AddComponent()
		{
			return Parent->AddComponent<T>();
		}
	};
}