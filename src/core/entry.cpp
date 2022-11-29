// 2022 Tygo Boons

// Using SFML graphics library
// found at https://www.sfml-dev.org/

#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Core.h"
#include "Game.h"
#include "Scene.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    // Allocate console if in debug configuration.
    ALLOC_CONSOLE()


    // Create game instance.
    Tmpl8::Game game(Tmpl8::Game::GetWindowProperties(), new Core::SceneManager());

    // Call game start method.
    game.Start();

    // Create sfml clock to use to get delta time.
    sf::Clock deltaClock;

    // Main window loop
    while (game.GetWindow()->isOpen())
    {

        // Poll SFML events.
        sf::Event event;
        while (game.GetWindow()->pollEvent(event))
        {
            // Poll window events.
            if (event.type == sf::Event::Closed)
            {
                game.GetWindow()->close();
            }
        }

        // Tick game instance
        sf::Time dt = deltaClock.restart();
        game.Tick(dt.asSeconds());
    }

    game.Shutdown();

    return 0;
}