#include "game.h"
#include <iostream>
#include <Windows.h>

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		m_CompositeFrameBuffer.create(m_Window->getSize().x, m_Window->getSize().y);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{

	}

	float xp, yp, scr = 10;
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		sf::Texture tex;
		if (!tex.loadFromFile("assets/ball.png"))
		{	
			std::cout << "rip zbozo";
		}

		sf::Sprite sprite(tex);

		m_CompositeFrameBuffer.clear(sf::Color(0, 100, 100));

		m_CompositeFrameBuffer.draw(sprite);

		m_CompositeFrameBuffer.display();

		m_Window->clear();
		m_Window->draw(sf::Sprite(m_CompositeFrameBuffer.getTexture()));
		m_Window->display();
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
		std::cout << x << " " << y << '\n';
	}

	void Game::KeyUp(int key)
	{
	}

	void Game::KeyDown(int key)
	{
		if(key == sf::Keyboard::Key::A)
			scr+= 10;

		if (key == sf::Keyboard::Key::D)
			scr-= 10;
	}

};