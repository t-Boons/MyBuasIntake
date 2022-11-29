// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Core.h"
#include "TestScene.h"
#include "Renderer/Renderer.h"

namespace Tmpl8 {

class Game
{
public:
	Game(sf::RenderWindow* window)
	{
		// Assign static window.
		s_Window = window;
	}

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

	static sf::RenderWindow* GetWindow() { return s_Window; }
	static Core::Scene* GetActiveScene() { return s_ActiveScene; }
	static void SetActiveScene(Core::Scene* scene) { s_ActiveScene = scene; }

private:
	static sf::RenderWindow* s_Window;
	static Core::Scene* s_ActiveScene;

	sf::View m_DefaultView;

};

}; // namespace Tmpl8