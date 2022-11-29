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


		m_Transform = std::make_shared<Entity::Transform>();
		m_Transform->SetPosition({ 0, 0, -5 });
		m_Transform->SetScale({ 0.1f, 0.1f, 0.1f });

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
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		Renderer::Renderer::BeginScene(m_Transform, m_Camera);

		Renderer::Renderer::Clear();
		m_Window->clear();
		Renderer::Renderer::SubmitMesh(m_Mesh, m_Material);

		pos.x += sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? 0 : 1 * deltaTime;
		pos.x -= sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? 0 : 1 * deltaTime;
		pos.y += sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ? 0 : 1 * deltaTime;
		pos.y -= sf::Keyboard::isKeyPressed(sf::Keyboard::E) ? 0 : 1 * deltaTime;
		pos.z += sf::Keyboard::isKeyPressed(sf::Keyboard::W) ? 0 : 1 * deltaTime;
		pos.z -= sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? 0 : 1 * deltaTime;
		rotation.y += sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) ? 200 * deltaTime : 0;

		m_Transform->SetPosition(pos);
		m_Transform->SetRotation(rotation);

		Renderer::Renderer::EndScene();

		m_Window->display();
	}
};