#pragma once
#include <stdint.h>

// Game instance class from
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include <SFML/Graphics.hpp>
#include "Core/Core.h"
#include "Renderer/TileSet.h"
#include "Gameplay/SkyBox.h"

namespace Tmpl8 {

class Game
{
public:
	Game(sf::RenderWindow* window)
		: m_Window(window)
	{}

	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);
	void KeyUp(int key);
	void KeyDown(int key);
private:
	sf::RenderWindow* m_Window;
	sf::RenderTexture m_CompositeFrameBuffer;
	Renderer::TileSet* m_Tiles;
	Gameplay::Skybox* m_SkyBox;
};

}; // namespace Tmpl8