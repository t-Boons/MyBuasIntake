// 2022 Tygo Boons

#include "mypch.h"
#include "Scene.h"

namespace Core
{
	void Scene::UnloadScene()
	{
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i].reset();
		}

		m_PhysicsEnviroment.reset();
	}

	void Scene::Start()
	{
		// Start all entity Components.
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->StartComponents();
		}
	}

	void Scene::Update()
	{
		// Here we loop through all to-be deleted object and remove them from the scene.
		ClearDeletionQueue();

		// Here all queued to-be instantiated objects get added to the scnee..
		ClearInstantiationQueue();
		
		// Update all entity Components.
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			m_Entities[i]->UpdateComponents();
		}
		
		// Update all physics.
		if (m_PhysicsEnviroment)
		{
			m_PhysicsEnviroment->Update();
		}

		// Update collision events for scriptcomponents.
		for (size_t i = 0; i < m_CollisionEvents.size(); i++)
		{
			auto entity = m_CollisionEvents[i]->ThisObject;
			
			if(entity)
			{
				entity->UpdateCollisionEvents(m_CollisionEvents[i]);
			}
		}

		// Reset collision events.
		m_CollisionEvents.clear();
	}

	void Scene::AddToScene(const RefPtr<Entity::GameObject>& object)
	{
		// Add pbodies and colliders if the object has any.
		auto pbody = object->GetComponent<Entity::PhysicsBody>();
		auto collider = object->GetComponent<Entity::BoxCollider>();

		if (pbody)
		{
			m_PhysicsEnviroment->RegisterComponent(pbody);
		}

		if (collider)
		{
			m_PhysicsEnviroment->RegisterComponent(collider);
		}

		// Add entity to component list.
		m_Entities.push_back(object);
	}

	void Scene::AddToScene(const std::vector<RefPtr<Entity::GameObject>>& objects)
	{
		// Add all objects to scene.
		for (auto& obj : objects)
		{
			AddToScene(obj);
		}
	}

	void Scene::ClearDeletionQueue()
	{
		// Loop through all to-be deleted object and remove them from the scene.
		for (size_t i = 0; i < m_DeletionQueue.size(); i++)
		{
			RemoveFromScene(m_DeletionQueue[i]);

			// Call start on component.
			m_DeletionQueue[i]->StartComponents();
		}

		// Clear the queue.
		m_DeletionQueue.clear();
	}


	void Scene::ClearInstantiationQueue()
	{
		// Loop through all to-be instantiated object and add them to the scene.
		for (size_t i = 0; i < m_InstantiationQueue.size(); i++)
		{
			AddToScene(m_InstantiationQueue[i]);

			// Call start on component.
			m_InstantiationQueue[i]->StartComponents();
		}

		// Clear the queue.
		m_InstantiationQueue.clear();
	}

	void Scene::RemoveFromScene(const RefPtr<Entity::GameObject>& object)
	{
		// Remove pbodies and colliders if the object has any.
		auto pbody = object->GetComponent<Entity::PhysicsBody>();
		auto collider = object->GetComponent<Entity::BoxCollider>();

		if (pbody)
		{
			m_PhysicsEnviroment->RemoveComponent(pbody);
		}

		if (collider)
		{
			m_PhysicsEnviroment->RemoveComponent(collider);
		}

		// Find object match.
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			if (m_Entities[i] == object)
			{
				// Remove object from array.
				m_Entities.erase(m_Entities.begin() + i);
			}
		}
	}

	RefPtr<Entity::GameObject> Scene::FindEntityByName(const std::string& name)
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

		LOG_WARN("Object: " + name + " can not be found.")

		return nullptr;
	}

	RefPtr<Entity::GameObject> Scene::FindEntityByID(uint64_t ID)
	{
		// See if any of the entity names match.
		for (auto& entity : m_Entities)
		{
			// Return if names match.
			if (entity->GetID() == ID)
			{
				return entity;
			}
		}

		LOG_WARN("Object with instance ID: " + STR(ID) + " can not be found.")

		return nullptr;
	}
}