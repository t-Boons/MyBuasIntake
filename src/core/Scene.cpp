// 2022 Tygo Boons

#include "Scene.h"

namespace Core
{
	void Scene::UnloadScene()
	{
		// Destroy this instance.
		delete(this);
	}

	void Scene::Update()
	{
		// Update all entity Components.
		for (auto& obj : m_Entities)
		{
			obj->UpdateComponents();
		}
	}

	void Scene::Start()
	{
		// Update all entity Components.
		for (auto& obj : m_Entities)
		{
			obj->StartComponents();
		}
	}

	void Scene::AddToScene(RefPtr<Entity::GameObject> object)
	{
		// Add entity to component list.
		m_Entities.push_back(object);
	}

	void Scene::RemoveFromScene(Entity::GameObject* object)
	{
		// Find object match.
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			if (m_Entities[i].get() == object)
			{
				// Remove object from array.
				m_Entities.erase(m_Entities.begin() + i);
			}
		}
	}

	const RefPtr<Entity::GameObject> Scene::FindEntityByName(const std::string& name)
	{
		// See if any of the entity names match.
		for (auto& entity : m_Entities)
		{
			// Return if names match.
			if (entity->GetName() == name)
			{
				return entity;
			}
		}

		return nullptr;
	}
}