// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "Game.h"
#include "Core/TestScene.h"
#include "Time.h"

namespace Tmpl8
{
	Game* Game::s_Instance = nullptr;


	// Initialize static cvariables.
	sf::RenderWindow* Game::GetWindowProperties()
	{
		sf::ContextSettings settings;
		settings.depthBits = 32;
		return new sf::RenderWindow(sf::VideoMode(1280, 720), "Wii - Tanks", 7U, settings);
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Start()
	{
		Renderer::Renderer::Init();

		GetSceneManager()->SetActiveScene(new Core::TestScene);

		m_SceneManager->GetActiveScene()->Start();

		//Temp.
		m_Camera = std::make_shared<Entity::Camera>();
	}

	void Game::UpdateTemporaryCameraMovement(float deltaTime)
	{

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::W) ? glm::vec3(0.0f) : m_Camera->GetViewForward() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? glm::vec3(0.0f) : -m_Camera->GetViewForward() * (deltaTime * 10);

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? glm::vec3(0.0f) : m_Camera->GetViewRight() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? glm::vec3(0.0f) : -m_Camera->GetViewRight() * (deltaTime * 10);

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::E) ? glm::vec3(0.0f) : m_Camera->GetViewUp() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ? glm::vec3(0.0f) : -m_Camera->GetViewUp() * (deltaTime * 10);

		glm::vec2 delta = (mDelta - glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) * 0.25f;
		mDelta = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			rotation.y += delta.x;
			rotation.x += delta.y;
		}

		m_Camera->SetViewPoint(pos);
		m_Camera->SetViewRotation(rotation);
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
		Renderer::Renderer::BeginScene(m_Camera);

		Renderer::Renderer::Clear();

		m_SceneManager->GetActiveScene()->Update();
		Core::Time::Tick();
		UpdateTemporaryCameraMovement(Core::Time::DeltaTime());

		Renderer::Renderer::EndScene();

		m_Window->display();
	}
};