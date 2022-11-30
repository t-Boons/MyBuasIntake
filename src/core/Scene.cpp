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
}