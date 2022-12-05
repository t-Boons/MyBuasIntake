// 2022 Tygo Boons
// This version is heavily modified
//
// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#pragma once

#include <SFML/Graphics.hpp>
#include "Core.h"
#include "Scene/SceneManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Material.h"
#include "Renderer/Mesh.h"
#include "Entity/Transform.h"
#include "Entity/Camera.h"

namespace Core
{

	class Game
	{
	public:
		Game(sf::RenderWindow* window, Core::SceneManager* sceneManager)
			: m_Window(window), m_SceneManager(sceneManager)
		{
			// Fill singleton instance with this.
			s_Instance = this;
		}

		// Runs when the game starts.
		void Start();

		// Runs when game is shut down.
		void Shutdown();

		// Runs every frame.
		void Tick();

		// Get window instance.
		inline sf::RenderWindow* GetWindow() const { return m_Window; }

		// Get scene manager instance.
		inline Core::SceneManager* GetSceneManager() const { return m_SceneManager; }

		// Static method to get the Game instance.
		static Game* Get() { return s_Instance; }

		// Get window initialization properties.
		static sf::RenderWindow* GetWindowProperties();

	private:
		sf::RenderWindow* m_Window;
		Core::SceneManager* m_SceneManager;

		static Game* s_Instance;

		RefPtr<Entity::Camera> m_Camera;


		glm::vec3 pos = { 0, 0, 0 };
		glm::vec3 rotation = { 0, 0, 0 };
		glm::vec2 mDelta = { 0, 0 };
	};

}; // namespace Tmpl8