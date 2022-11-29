// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "Game.h"

namespace Tmpl8
{
	// Initialize static cvariables.
	sf::RenderWindow* Game::s_Window = nullptr;
	Core::Scene* Game::s_ActiveScene = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Start()
	{
		SetActiveScene(new Core::TestScene());
		GetActiveScene()->LoadScene();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete GetActiveScene();
		delete GetWindow();
	}

	float xp, yp, size = 1;
	sf::Vector2f pos = { 0, 0 };

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		UpdateObjects(deltaTime);
		RenderScene();
	}

	void Game::MouseUp(int button)
	{
	}

	void Game::MouseDown(int button)
	{
	}

	void Game::MouseMove(int x, int y)
	{
		xp = (float)x; yp = (float)y;
	}

	void Game::KeyUp(int key)
	{
	}

	void Game::KeyDown(int key)
	{

	}

	void Game::RenderScene()
	{

		// Clear the composite frame buffer.
		Renderer::Renderer::Clear();

		Renderer::Renderer::SubmitMesh(nullptr);
	}

	void Game::UpdateObjects(float deltaTime)
	{
		float s = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ? 1500 : 500) * deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			pos.x -= s;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			pos.x += s;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			pos.y -= s;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			pos.y += s;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			size -= 1 * deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
			size += 1 * deltaTime;

		if (size < 0)
			size = 0.001f * deltaTime;

		m_DefaultView = sf::View(sf::Vector2f(s_Window->getSize().x / 2, s_Window->getSize().y / 2) + pos, (sf::Vector2f)s_Window->getSize() * size);

	}

};