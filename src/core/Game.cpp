// Game instance class from:
// Template, BUAS version https://www.buas.nl/games
// IGAD / BUAS(NHTV) / UU - Jacco Bikker - 2006 - 2020

#include "Game.h"
#include "Core/TestScene.h"

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

		m_Mesh = std::make_shared<Renderer::Mesh>();
		m_Mesh->LoadMesh("assets/Tanks/TankPlayer.obj");

		m_Material = std::make_shared<Renderer::Material>();
		m_Material->Shader = new Renderer::Shader("assets/shaders/Basic3DShader.glsl");
		m_Material->Texture->loadFromFile("assets/Tanks/textures/enemy/tank_marin.png");

		m_Camera = std::make_shared<Entity::Camera>();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{

	}
	glm::vec3 pos = { 0, 0, 0 };
	glm::vec3 rotation = { 0, 0, 0 };
	glm::vec2 mDelta = { 0, 0 };
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	float dt = 0;
	void Game::Tick(float deltaTime)
	{
		Renderer::Renderer::BeginScene(m_Camera);

		Renderer::Renderer::Clear();

		RefPtr<Entity::Transform> tr = std::make_shared<Entity::Transform>();
		dt += deltaTime;
		tr->SetPosition({ 0, 0, sin(dt * 10) * 5});
		tr->SetScale({ 0.1f, 0.1f, 0.1f });
		Renderer::Renderer::SubmitMesh(tr, m_Mesh, m_Material);

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::W) ? glm::vec3(0.0f) : m_Camera->GetForward() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? glm::vec3(0.0f) : -m_Camera->GetForward() * (deltaTime * 10);

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? glm::vec3(0.0f) : m_Camera->GetRight() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? glm::vec3(0.0f) : -m_Camera->GetRight() * (deltaTime * 10);

		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::E) ? glm::vec3(0.0f) : m_Camera->GetUp() * (deltaTime * 10);
		pos += sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ? glm::vec3(0.0f) : -m_Camera->GetUp() * (deltaTime * 10);

		glm::vec2 delta = (mDelta - glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) * 0.25f;
		mDelta = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
				rotation.y += delta.x;
				rotation.x += delta.y;
		}

		m_Camera->SetPosition(pos);
		m_Camera->SetRotation(rotation);

		Renderer::Renderer::EndScene();

		m_Window->display();
	}
};