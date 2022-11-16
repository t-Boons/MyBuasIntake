// Game instance class from
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Core/Core.h"
#include "Object/TileSet.h"
#include "Object/SkyBox.h"
#include "Object/Player.h"

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

	void RenderScene();
	void UpdateObjects(float deltaTime);

private:
	sf::RenderWindow* m_Window;
	sf::RenderTexture m_CompositeFrameBuffer;
	sf::View m_DefaultView;
	std::vector<Object::Object*> m_Objects;
};

}; // namespace Tmpl8