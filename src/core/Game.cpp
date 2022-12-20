// Tygo Boons 2022

// Game instance class partly from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "mypch.h"

#include "Game.h"
#include "Time.h"
#include "Input.h"
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

		GetSceneManager()->SetActiveScene(new Gameplay::Level1());
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		LOG_WARN("Shutting down Game")
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

		// Clear all input handler inputs.
		Input::Flush();
	}

	void Game::OnEvent(sf::Event& event)
	{
		// Send all events to the input handler.
		Input::SendEvent(event);
	}

	RefPtr<Window> Game::GetWindowProperties()
	{
		// Create context settings object.
		sf::ContextSettings settings;
		settings.depthBits = 32;
		settings.antialiasingLevel = 2;

		// Create resolution.
		glm::ivec2 resolution = { 1920 , 1080 };

		// Create windowproperties instance and set it.
		Core::WindowProperties properties;
		properties.ContextSettings = settings;
		properties.Resolution = resolution;
		properties.Name = "Wii Tanks - BUAS Intake Tygo Boons";
		properties.Style = sf::Style::Fullscreen;

		return Core::Window::Create(properties);
	}
};