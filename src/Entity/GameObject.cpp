// 2022 Tygo Boons

#include "GameObject.h"

namespace Entity
{
	void GameObject::UpdateComponents()
	{
		// Loop through all components
		for (auto& c : m_Components)
		{
			c->Update();
		}
	}

	void GameObject::Destroy()
	{
		m_Components.clear();
		delete(this);
	}
}