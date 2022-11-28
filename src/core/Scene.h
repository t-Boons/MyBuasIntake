// 2022 Tygo Boons

#pragma once
#include <vector>
#include <string>
#include "Core.h"
#include "Entity/GameObject.h"

namespace Core
{
	class Scene
	{
	public:

		// Load this scene and instantiate all game objects.
		virtual void LoadScene() = 0;

		// Destroy all gameobjects and unload the scene.
		void UnloadScene();

		// Update scene.
		void Update();

		// Return reference to GameObject vector.
		const std::vector<RefPtr<Entity::GameObject>>& GetEntities() const { return m_Entities; }

	protected:
		std::vector<RefPtr<Entity::GameObject>> m_Entities;
		std::string m_Name;
	};
}