// 2022 Tygo Boons

#include "mypch.h"
#include "TextureAtlas.h"

namespace Utils
{

	// Initialize class variables
	TextureAtlas::TextureAtlas(const std::string& filepath,  uint32_t tileSize)
		: m_TileSize(tileSize)
	{
		// Create texture with filepath.
		sf::Texture tex;
		if(!tex.loadFromFile(filepath))
		{
			ASSERT(false, "Texture file can not be loaded.")
		}

		ASSERT(tileSize != 0, "TileSize can not be 0")
		
		// Assign texture to this texture atlas.
		m_Texture = tex;
		m_Size = tex.getSize();
	}

	std::array<sf::Vector2f, 4> TextureAtlas::GetTextureCoordinates(uint32_t index)
	{
		// Initialize x & y variables.
		float x = 0;
		float y = 0;

		// Calculate coordinate based on index.
		if (index != 0)
		{
			x = static_cast<float>(index % (m_Size.x / m_TileSize));
			y = static_cast<float>(index / (m_Size.x / m_TileSize));
		}

		ASSERT(y < (m_Size.x / m_TileSize), "Index out of range");

		return GetTextureCoordinates(sf::Vector2u(static_cast<uint32_t>(x), static_cast<uint32_t>(y)));
	}

	std::array<sf::Vector2f, 4> TextureAtlas::GetTextureCoordinates(const sf::Vector2u& coordinate)
	{
		// Convert coordinates to amount in pixels.
		float x = static_cast<float>(static_cast<uint32_t>(coordinate.x * m_TileSize));
		float y = static_cast<float>(static_cast<uint32_t>(coordinate.y * m_TileSize));

		ASSERT(x <= m_Size.x, "Index out of range")
		ASSERT(y <= m_Size.y, "Index out of range")

		// Return array of texture coordinates that correspond to the coordinates on the texture.
		return
		{
			sf::Vector2f(x, y),
			sf::Vector2f(x + m_TileSize, y),
			sf::Vector2f(x + m_TileSize, y + m_TileSize),
			sf::Vector2f(x, y + m_TileSize),
		};
	}
}