// 2022 Tygo Boons

#include "GameObject.h"
#include "Transform.h"
#include "Core/Game.h"

namespace Entity
{
	GameObject::GameObject(const std::string& name)
		: m_Name(name)
	{
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
			if (c)
			{
				c->Update();
			}
		}
	}

	void GameObject::Destroy()
	{
		// TODO Make it so it deletes properly after the update loop.
		m_Components.clear();
	}

	RefPtr<GameObject> GameObject::Find(const std::string& name)
	{
		return Core::Game::Get()->GetSceneManager()->GetActiveScene()->FindEntityByName(name);
	}
}