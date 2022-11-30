// 2022 Tygo Boons

#include "Component.h"

namespace Entity
{
	void Component::SetParent(GameObject* parent)
	{
		Parent = parent;
	}
}