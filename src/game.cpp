#include "game.h"
#include <iostream>
#include <Windows.h>

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		m_CompositeFrameBuffer.create(m_Window->getSize().x, m_Window->getSize().y);

		m_Atlas = new Renderer::TextureAtlas("assets/PixelArtPlatformer_Village Props_v2.1.0/tx_chest_animation.png", 32);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete m_Atlas;
	}

	float xp, yp, scr = 10;
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		m_CompositeFrameBuffer.clear(sf::Color(0, 100, 100));
		{
			sf::VertexArray skybox(sf::Quads, 4);

			sf::Texture skyboxTex;
			skyboxTex.loadFromFile("assets/pixelskybox.png");

			skybox[0] = sf::Vertex({ 0.0f, 0.0f }, {0.0f, 0.0f});
			skybox[1] = sf::Vertex({ 0.0f, (float)m_Window->getSize().y }, { 0.0f, (float)skyboxTex.getSize().y });
			skybox[2] = sf::Vertex({ (float)m_Window->getSize().x, (float)m_Window->getSize().y }, { (float)skyboxTex.getSize().x, (float)skyboxTex.getSize().y });
			skybox[3] = sf::Vertex({ (float)m_Window->getSize().x, 0.0f }, { (float)skyboxTex.getSize().x, 0.0f });


			sf::RenderStates states;
			states.texture = &skyboxTex;

			m_CompositeFrameBuffer.draw(skybox, states);
		}

		{
			sf::VertexArray va(sf::Quads, 4);

			va[0].position = { 0, 0 };
			va[0].texCoords = m_Atlas->GetTextureCoordinates({0, 1})[0];

			va[1].position = { 50, 0 };
			va[1].texCoords = m_Atlas->GetTextureCoordinates({ 0, 1 })[1];

			va[2].position = { 50, 50 };
			va[2].texCoords = m_Atlas->GetTextureCoordinates({ 0, 1 })[2];

			va[3].position = { 0, 50 };
			va[3].texCoords = m_Atlas->GetTextureCoordinates({ 0, 1 })[3];


			sf::Transform transform;
			transform.translate({ xp, yp });
			sf::RenderStates states;

			states.texture = m_Atlas->GetTexture();
			states.transform = transform;

			m_CompositeFrameBuffer.draw(va, states);
		}

		m_CompositeFrameBuffer.display();

		m_Window->clear();
		m_Window->draw(sf::Sprite(m_CompositeFrameBuffer.getTexture()));
		m_Window->display();
	}

	void Game::MouseUp(int button)
	{
	}

	void Game::MouseDown(int button)
	{
	}

	void Game::MouseMove(int x, int y)
	{
		xp = (float)x; yp = (float)y;
	}

	void Game::KeyUp(int key)
	{
	}

	void Game::KeyDown(int key)
	{
		if(key == sf::Keyboard::Key::A)
			scr+= 10;

		if (key == sf::Keyboard::Key::D)
			scr-= 10;
	}

};