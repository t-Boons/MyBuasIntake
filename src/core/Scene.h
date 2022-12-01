// 2022 Tygo Boons

#pragma once
#include <vector>
#include <string>
#include "Core.h"
#include "Entity/GameObject.h"
#include "Entity/Camera.h"

namespace Core
{
	class Scene
	{
	public:

		// Load this scene and instantiate all game objects.
		virtual void LoadScene() = 0;

		// Destroy all gameobjects and unload the scene.
		void UnloadScene();

		// start scene.
		void Start();

		// Update scene.
		void Update();

		// Spawn game object
		void AddToScene(RefPtr<Entity::GameObject> object);

		// Removes game object from scene
		void RemoveFromScene(Entity::GameObject* object);

		// Return reference to GameObject vector.
		const std::vector<RefPtr<Entity::GameObject>>& GetEntities() const { return m_Entities; }

		// Set active render camera.
		void SetActiveCamera(const RefPtr<Entity::Camera>& camera) { m_ActiveCamera = camera; }

		// Get active render camera.
		const RefPtr<Entity::Camera> GetActiveCamera() const { return m_ActiveCamera; }

		// Finds the entity with name.
		const RefPtr<Entity::GameObject> FindEntityByName(const std::string& name);

	protected:
		std::vector<RefPtr<Entity::GameObject>> m_Entities;
		RefPtr<Entity::Camera> m_ActiveCamera;
	};
}