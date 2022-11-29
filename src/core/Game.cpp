// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "Game.h"
#include "Core/TestScene.h"

namespace Tmpl8
{
	Game* Game::s_Instance = nullptr;


	// Initialize static cvariables.
	sf::RenderWindow* Game::GetWindowProperties()
	{
		return new sf::RenderWindow(sf::VideoMode(1280, 720), "Wii - Tanks");
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Start()
	{
		Renderer::Renderer::Init();

		Get()->GetSceneManager()->SetActiveScene(new Core::TestScene);
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
	void Game::Tick(float deltaTime)
	{

	}
};