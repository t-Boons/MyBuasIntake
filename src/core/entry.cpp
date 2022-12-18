// 2022 Tygo Boons

// Using SFML graphics library
// found at https://www.sfml-dev.org/

#include "mypch.h"

#include <Windows.h>

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Core.h"
#include "Game.h"
#include "Scene/Scene.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{

	// Create window instance.
	Core::WindowProperties properties;

	// Create context settings object.
	sf::ContextSettings settings;
	settings.depthBits = 32;

	// Create resolution.
	glm::ivec2 resolution = { 1280, 720 };

	properties.ContextSettings = settings;
	properties.Resolution = resolution;

	RefPtr<Core::Window> window = Core::Window::Create(properties);


	// Create game instance.
	Core::Game game(window);

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