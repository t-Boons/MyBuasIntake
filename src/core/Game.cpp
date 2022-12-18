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

		GetSceneManager()->SetActiveScene(new Gameplay::Level1);

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

		Renderer::Renderer::Clear({0.15f, 0.2f, 0.24f});

		Core::Time::Tick();
		m_SceneManager->GetActiveScene()->Update();

		Renderer::Renderer::EndScene();

		m_Window->display();
	}

	glm::vec2 Game::GetNormalizedMousePosition() const
	{
		// Get screen size and mouse position.
		sf::Vector2u screenSize = Core::Game::Get()->GetWindow()->getSize();
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*Core::Game::Get()->GetWindow());

		// Get normalized screen position and change coordinate origin to the bottom left of the screen.
		glm::vec2 normalizedPosition = glm::vec2(static_cast<float>(mousePosition.x) / static_cast<float>(screenSize.x),
			-static_cast<float>(mousePosition.y) / static_cast<float>(screenSize.y) + 1.0f);

		return normalizedPosition;
	}
};