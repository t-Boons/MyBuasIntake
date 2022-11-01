#include "game.h"

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		m_CompositeFrameBuffer.create(m_Window->getSize().x, m_Window->getSize().y);

		Renderer::TileProperties properties;
		properties.ColorReferenceMap = "assets/PixelArtPlatformer_Village Props_v2.1.0/tx_tileset_ground_colorreference.png";
		properties.TextureMap = "assets/PixelArtPlatformer_Village Props_v2.1.0/tx_tileset_ground.png";
		properties.ColorMap = "assets/PixelArtPlatformer_Village Props_v2.1.0/tx_tileset_ground_colormap.png";
		properties.TextureMapTileSizeInPixels = 32;
		properties.TileSizeInGame = 32;

		m_Tiles = new Renderer::TileSet(properties);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete m_Tiles;
	}

	float xp, yp;
	sf::Vector2f pos = { 0, 0 };

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		m_CompositeFrameBuffer.clear(sf::Color(0, 100, 100));

		m_CompositeFrameBuffer.setView(sf::View(sf::Vector2f(m_Window->getSize().x / 2, m_Window->getSize().y / 2), (sf::Vector2f)m_Window->getSize()));

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

			m_CompositeFrameBuffer.setView(sf::View(sf::Vector2f(m_Window->getSize().x / 2, m_Window->getSize().y / 2) + pos, (sf::Vector2f)m_Window->getSize()));

			sf::RenderStates s;
			s.texture = m_Tiles->GetTexture();
			m_CompositeFrameBuffer.draw(m_Tiles->GetVertexArray(), s);
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
		float s = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ? 50 : 10;

		if(key == sf::Keyboard::Key::A)
			pos.x -= s;

		if (key == sf::Keyboard::Key::D)
			pos.x += s;

		if (key == sf::Keyboard::Key::W)
			pos.y -= s;

		if (key == sf::Keyboard::Key::S)
			pos.y += s;
	}

};