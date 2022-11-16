#include "Game.h"

namespace Tmpl8
{

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		// Initialize frame buffer object to render the scene to.
		m_CompositeFrameBuffer.create(m_Window->getSize().x, m_Window->getSize().y);


		// Initialize tileset.
		Object::TileProperties properties;
		properties.ColorReferenceMap = "assets/PixelArtPlatformer_Village Props_v2.1.0/tx_tileset_ground_colorreference.png";
		properties.TextureMap = "assets/PixelArtPlatformer_Village Props_v2.1.0/tx_tileset_ground.png";
		properties.ColorMap = "assets/PixelArtPlatformer_Village Props_v2.1.0/tx_tileset_ground_colormap.png";
		properties.TextureMapTileSizeInPixels = 32;
		properties.TileSizeInGame = 32;

		Object::Object* worldTiles = new Object::TileSet(properties);


		// Create skybox.
		Object::Object* skyBox = new Object::Skybox("assets/pixelskybox.png", m_Window->getSize());


		// Create player
		Object::Object* player = new Object::Player("assets/TestPlayer.png", 32);

		// Add initialized objects to object vector.
		m_Objects.push_back(skyBox);
		m_Objects.push_back(player);
		m_Objects.push_back(worldTiles);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		// Free all object memory.
		for (Object::Object* obj : m_Objects)
		{
			delete(obj);
		}
	}

	float xp, yp, size = 1;
	sf::Vector2f pos = { 0, 0 };

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		UpdateObjects(deltaTime);
		RenderScene();
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

	}

	void Game::RenderScene()
	{

		// Clear the composite frame buffer.
		m_CompositeFrameBuffer.clear(sf::Color(0, 100, 100));

		//--------------------//
		// Render all objects.//
		//--------------------//

		for (auto& obj : m_Objects)
		{
			// Set a custom viewport for renderable object if the GetViewport method is overridden.
			m_CompositeFrameBuffer.setView(obj->GetViewport() != nullptr ? *obj->GetViewport() : m_DefaultView);

			// Select texture to sample from.
			sf::RenderStates states;
			states.texture = obj->GetTexture();

			// Draw opject to composite frame buffer.
			m_CompositeFrameBuffer.draw(obj->GetVertexArray(), states);
		}

		// Show frame buffer
		m_CompositeFrameBuffer.display();

		// Draw composite frame buffer to the screen.
		m_Window->clear();
		m_Window->draw(sf::Sprite(m_CompositeFrameBuffer.getTexture()));
		m_Window->display();
	}

	void Game::UpdateObjects(float deltaTime)
	{
		for (auto& obj : m_Objects)
		{
			obj->Update(deltaTime);
		}


		float s = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ? 1500 : 500) * deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			pos.x -= s;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			pos.x += s;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			pos.y -= s;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			pos.y += s;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			size -= 1 * deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
			size += 1 * deltaTime;

		if (size < 0)
			size = 0.001f * deltaTime;

		m_DefaultView = sf::View(sf::Vector2f(m_Window->getSize().x / 2, m_Window->getSize().y / 2) + pos, (sf::Vector2f)m_Window->getSize() * size);

	}

};