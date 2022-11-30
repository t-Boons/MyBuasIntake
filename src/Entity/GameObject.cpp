// 2022 Tygo Boons

#include "GameObject.h"
#include "Transform.h"

namespace Entity
{
	GameObject::GameObject(const std::string& name)
		: m_Name(name)
	{
		// Set default name if object does not have a name.
		if (m_Name == "")
		{
			m_Name = "New Game Object";
		}

		// Add default Transform Component.
		RefPtr<Transform> a(new Transform);
		AddComponent(a);
	}

	void GameObject::StartComponents()
	{
		// Loop through all components
		for (auto& c : m_Components)
		{
			c->Start();
		}
	}

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