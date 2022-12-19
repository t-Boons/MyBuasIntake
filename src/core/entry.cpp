// 2022 Tygo Boons

#include "mypch.h"

#include <Windows.h>
#include <SFML/System.hpp>
#include "Core.h"
#include "Game.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{

	// Create game instance.
	Core::Game game(Core::Game::GetWindowProperties());

	// Call game start method.
	game.Start();

	// Create sfml clock to use to get delta time.
	sf::Clock deltaClock;

	// Main window loop
	while (game.GetWindow()->IsOpen())
	{

		// Poll SFML events.
		sf::Event event;
		while (game.GetWindow()->PollEvent(event))
		{
			// Poll window close event.
			if (event.type == sf::Event::Closed)
			{
				game.GetWindow()->Close();
			}
		}

		// Update game loop.
		game.Tick();

	}

	// Close the game.
	game.Shutdown();

	return 0;
}