// 2022 Tygo Boons

#pragma once

#include "Core/Core.h"
#include "Entity/GameObject.h"
#include "Entity/Camera.h"
#include "Physics/Physics.h"

#define SCENE_NAME(name) public: virtual std::string GetSceneName() override {return #name;}

namespace Core
{
	class Scene
	{
	public:
		Scene();

		// Returns the scene name
		virtual std::string GetSceneName() = 0;

		// Load this scene and instantiate all game objects.
		virtual void LoadScene() = 0;

		// Destroy all gameobjects and unload the scene.
		void UnloadScene();

		// start scene.
		void Start();

		// Update scene.
		void Update();

		// Spawn game object
		void AddToScene(const RefPtr<Entity::GameObject>& object);

		// Spawns multiple game objects.
		void AddToScene(const std::vector<RefPtr<Entity::GameObject>>& objects);

		// Instantiate all object in instantiation queue.
		void ClearInstantiationQueue();

		// Adds object to instantiation queue
		void AddEntityToInstantiationQueue(const RefPtr<Entity::GameObject> object) { m_InstantiationQueue.push_back(object); }

		// Instantiate all object in instantiation queue.
		void ClearDeletionQueue();

		// Adds object to instantiation queue
		void AddEntityToDeletionQueue(const RefPtr<Entity::GameObject> object) { m_DeletionQueue.push_back(object); }

		// Removes game object from scene
		void RemoveFromScene(const RefPtr<Entity::GameObject>& object);

		// Return reference to GameObject vector.
		const std::vector<RefPtr<Entity::GameObject>>& GetEntities() const { return m_Entities; }

		// Set active render camera.
		void SetActiveCamera(const RefPtr<Entity::Camera>& camera) { m_ActiveCamera = camera; }

		// Get active render camera.
		const RefPtr<Entity::Camera>& GetActiveCamera() const { return m_ActiveCamera; }

		// Finds the entity with name.
		RefPtr<Entity::GameObject> FindEntityByName(const std::string& name);

		// Finds the entity with Instance ID.
		RefPtr<Entity::GameObject> FindEntityByID(uint64_t ID);

		// Add a collision event that will be ran next frame.
		void AddCollisionEnterEvent(RefPtr<Physics::Collision> collision) { m_CollisionEvents.push_back(collision); }

		template<typename T>
		RefPtr<T> FindObjectOfType()
		{
			// Loop through all entities.
			for (auto& entity : m_Entities)
			{
				// Try to get the requested component.
				RefPtr<T> component = entity->GetComponent<T>();

				// If component found return it.
				if (component)
				{
					return component;
				}
			}

			return nullptr;
		}

		template<typename T>
		std::vector<RefPtr<T>> FindObjectsOfType()
		{
			std::vector<RefPtr<T>> components;

			// Loop through all entities.
			for (auto& entity : m_Entities)
			{
				// Try to get the requested component.
				RefPtr<T> component = entity->GetComponent<T>();

				// If component found return it.
				if (component)
				{
					components.push_back(component);
				}
			}

			return components;
		}

	protected:
		std::vector<RefPtr<Entity::GameObject>> m_Entities;
		std::vector<RefPtr<Entity::GameObject>> m_InstantiationQueue;
		std::vector<RefPtr<Entity::GameObject>> m_DeletionQueue;
		std::vector<RefPtr<Physics::Collision>> m_CollisionEvents;
		RefPtr<Entity::Camera> m_ActiveCamera;

	};
}