// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "mypch.h"
#include "Game.h"
#include "Time.h"
#include "Game/Scenes/Level1.h"

namespace Core
{
	Game* Game::s_Instance = nullptr;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Start()
	{
		Renderer::Renderer::Init();

		m_SceneManager = SceneManager::Create();

		GetSceneManager()->SetActiveScene(new Gameplay::Level1);

		m_SceneManager->GetActiveScene()->Start();
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{

	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick()
	{
		Renderer::Renderer::BeginScene(m_SceneManager->GetActiveScene()->GetActiveCamera());

		Renderer::Renderer::Clear({0.15f, 0.2f, 0.24f});

		Core::Time::Tick();
		m_SceneManager->GetActiveScene()->Update();

		Renderer::Renderer::EndScene();

		m_Window->Display();
	}
};