// 2022 Tygo Boons

#pragma once

#include "Core/Core.h"
#include "Entity/GameObject.h"
#include "Entity/Camera.h"
#include "Physics/PhysicsEnviroment.h"

namespace Core
{
	class Scene
	{
	public:

		Scene()
			: m_PhysicsEnviroment(Physics::PhysicsEnviroment::Create())
		{}

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

		// Get physics scene component.
		const RefPtr<Physics::PhysicsEnviroment>& GetPhysicsEnviroment() const { return m_PhysicsEnviroment; }

		// Finds the entity with name.
		RefPtr<Entity::GameObject> FindEntityByName(const std::string& name);

		// Finds the entity with Instance ID.
		RefPtr<Entity::GameObject> FindEntityByID(uint64_t ID);

		// Add a collision event that will be ran next frame.
		void AddCollisionEnterEvent(RefPtr<Physics::Collision> collision) { m_CollisionEvents.push_back(collision); }

	protected:
		std::vector<RefPtr<Entity::GameObject>> m_Entities;
		std::vector<RefPtr<Entity::GameObject>> m_InstantiationQueue;
		std::vector<RefPtr<Entity::GameObject>> m_DeletionQueue;
		std::vector<RefPtr<Physics::Collision>> m_CollisionEvents;
		RefPtr<Physics::PhysicsEnviroment> m_PhysicsEnviroment;
		RefPtr<Entity::Camera> m_ActiveCamera;

	};
}