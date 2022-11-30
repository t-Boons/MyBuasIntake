// 2022 Tygo Boons

#pragma once
#include "Entity/Component.h"

namespace Gameplay
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

		// AddComponent to this gameobject.
		template<class T>
		const RefPtr<T> AddComponent()
		{
			return Parent->AddComponent<T>();
		}
	};
}