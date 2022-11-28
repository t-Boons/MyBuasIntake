// 2022 Tygo Boons

#include "GameObject.h"

namespace Entity
{
	uint32_t GameObject::s_CurrentObjectID = 0;

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
		s_CurrentObjectID--;
		m_Components.clear();
		delete(this);
	}
}