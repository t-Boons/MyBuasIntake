// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "mypch.h"
#include "Game.h"
#include "Time.h"
#include "Game/Scenes/Level1.h"

namespace Core
{
	Game* Game::s_Instance = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Start()
	{
		Renderer::Renderer::Init();

		m_SceneManager = SceneManager::Create();

		GetSceneManager()->SetActiveScene(new Gameplay::Level1);
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		LOG_WARN("Shutting down Engine")
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick()
	{
		// Start rendering of the scene.
		Renderer::Renderer::BeginScene(m_SceneManager->GetActiveScene()->GetActiveCamera());

		// Clear the old screen buffer.
		Renderer::Renderer::Clear({0.15f, 0.2f, 0.24f});
		
		// Update timing values.
		Core::Time::Tick();

		// Update physics, behaviour and render the actual objects.
		m_SceneManager->GetActiveScene()->Update();

		// Finish the rendering.
		Renderer::Renderer::EndScene();

		// Display the rendered frame.
		m_Window->Display();
	}

	RefPtr<Window> Game::GetWindowProperties()
	{
		// Create context settings object.
		sf::ContextSettings settings;
		settings.depthBits = 32;

		// Create resolution.
		glm::ivec2 resolution = { 1280, 720 };

		// Create windowproperties instance and set it.
		Core::WindowProperties properties;
		properties.ContextSettings = settings;
		properties.Resolution = resolution;
		properties.Name = "Wii Tanks - BUAS Intake Tygo Boons";

		return Core::Window::Create(properties);
	}
};