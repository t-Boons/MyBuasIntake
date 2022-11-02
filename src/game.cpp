#include "game.h"
#include "Utils/ColorLookupMap.h"
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

		m_SkyBox = new Gameplay::Skybox("assets/pixelskybox.png", m_Window->getSize());
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete m_Tiles;
		delete m_SkyBox;
	}

	float xp, yp, size = 1;
	sf::Vector2f pos = { 0, 0 };

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		m_CompositeFrameBuffer.clear(sf::Color(0, 100, 100));

		// Render skybox object.
		m_CompositeFrameBuffer.setView(m_SkyBox->GetView());

		sf::RenderStates states;
		states.texture = m_SkyBox->GetTexture();

		m_CompositeFrameBuffer.draw(m_SkyBox->GetVertexArray(), states);


		{

			m_CompositeFrameBuffer.setView(sf::View(sf::Vector2f(m_Window->getSize().x / 2, m_Window->getSize().y / 2) + pos, (sf::Vector2f)m_Window->getSize() * size));

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

		if (key == sf::Keyboard::Key::Q)
			size -= 0.05f;

		if (key == sf::Keyboard::Key::E)
			size += 0.05f;

		if (size < 0)
			size = 0.001f;
	}

};