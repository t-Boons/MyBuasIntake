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

	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{

	}

	float xp, yp;
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		m_Window->clear(sf::Color(0, 50, 50));

		sf::CircleShape shape(25);
		shape.setFillColor(sf::Color(100, 250, 50));
		shape.setPosition({ xp, yp});
		m_Window->draw(shape);
	}

	void Game::MouseUp(int button)
	{
	}

	void Game::MouseDown(int button)
	{
	}

	void Game::MouseMove(int x, int y)
	{
		xp = x; yp = y;
		std::cout << x << " " << y << '\n';
	}

	void Game::KeyUp(int key)
	{
	}

	void Game::KeyDown(int key)
	{
	}

};