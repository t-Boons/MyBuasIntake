// Copyright (C) 2022 Tygo Boons
// All rights reserved.

// Using SFML graphics library
// found at https://www.sfml-dev.org/

#if !defined(_WIN32) && !defined(WIN64)
#error This project only supports Windows
#endif

#ifdef _DEBUG

#define ALLOC_CONSOLE() __pragma(warning(push))          \
                        __pragma(warning(disable:6031))  \
                        AllocConsole();                  \
                        freopen("CONOUT$", "w", stdout); \
                        __pragma (warning(pop))
#else
#define ALLOC_CONSOLE() ;;
#endif


#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <Windows.h>
#include "../game.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    // Allocate console if in debug configuration.
    ALLOC_CONSOLE()

    // Create window instance.
	sf::RenderWindow window(sf::VideoMode(800, 600), "Template");

    // Create game instance.
    Tmpl8::Game game(&window);
    game.Init();

    // Create sfml clock to use to get delta time.
    sf::Clock deltaClock;

    // Main window loop
    while (window.isOpen())
    {

        // Poll SFML events.
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Poll key events.
            if (event.type == sf::Event::KeyPressed)
                game.KeyDown(event.key.code);

            if (event.type == sf::Event::KeyReleased)
                game.KeyUp(event.key.code);

            // Poll mouse events.
            if (event.type == sf::Event::MouseButtonPressed)
                game.MouseDown(event.mouseButton.button);

            if (event.type == sf::Event::MouseButtonReleased)
                game.MouseUp(event.mouseButton.button);

            if (event.type == sf::Event::MouseMoved)
                game.MouseMove(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

            // Poll window events.
            if (event.type == sf::Event::Closed)
            {
                game.Shutdown();
                window.close();
            }
        }



        // Tick game instance
        sf::Time dt = deltaClock.restart();
        game.Tick(dt.asSeconds());

        // Update window.
        window.display();
    }


    return 0;
}