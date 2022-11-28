// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "Game.h"

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		m_ActiveScene = std::make_shared<Core::TestScene>();
		m_ActiveScene->LoadScene();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{

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
		m_CompositeFrameBuffer.clear(sf::Color(0, 100, 100));

		// Show frame buffer
		m_CompositeFrameBuffer.display();

		// Draw composite frame buffer to the screen.
		m_Window->clear();
		m_Window->draw(sf::Sprite(m_CompositeFrameBuffer.getTexture()));
		m_Window->display();
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

		m_DefaultView = sf::View(sf::Vector2f(m_Window->getSize().x / 2, m_Window->getSize().y / 2) + pos, (sf::Vector2f)m_Window->getSize() * size);

	}

};