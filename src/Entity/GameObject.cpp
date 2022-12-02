// 2022 Tygo Boons

#include "mypch.h"
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
		// Return if object has to be deleted.
		if (QueuedForDeletion())
			return;

		// Loop through all components
		for (size_t i = 0; i < m_Components.size(); i++)
		{
			m_Components[i]->Update();
		}
	}

	void GameObject::Destroy()
	{
		ASSERT(this != nullptr, "The object you're trying to destroy is nullptr.")

		m_QueueForDeletion = true;
	}

	bool GameObject::QueuedForDeletion()
	{
		if (m_QueueForDeletion)
		{
			// Delete components.
			m_Components.clear();

			// Remove this object from the scene.
			Core::Game::Get()->GetSceneManager()->GetActiveScene()->RemoveFromScene(this);
		}

		return m_QueueForDeletion;
	}

	const RefPtr<GameObject>& GameObject::Find(const std::string& name)
	{
		return Core::Game::Get()->GetSceneManager()->GetActiveScene()->FindEntityByName(name);
	}
}