// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "Game.h"
#include "Core/TestScene.h"
#include "Time.h"

namespace Core
{
	Game* Game::s_Instance = nullptr;

	// Initialize static cvariables.
	sf::RenderWindow* Game::GetWindowProperties()
	{
		sf::ContextSettings settings;
		settings.depthBits = 32;
		return new sf::RenderWindow(sf::VideoMode(1280, 720), "Wii - Tanks", 7U, settings);
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Start()
	{
		Renderer::Renderer::Init();

		GetSceneManager()->SetActiveScene(new Core::TestScene);

		m_SceneManager->GetActiveScene()->Start();
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{

	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick()
	{
		Renderer::Renderer::BeginScene(m_SceneManager->GetActiveScene()->GetActiveCamera());

		Renderer::Renderer::Clear();

		m_SceneManager->GetActiveScene()->Update();
		Core::Time::Tick();

		Renderer::Renderer::EndScene();

		m_Window->display();
	}
};