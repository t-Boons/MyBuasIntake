// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#pragma once
#include <string>
#include <array>
#include "core/core.h"
#include <SFML/Graphics.hpp>

namespace Renderer
{
	class TextureAtlas
	{
	public:
		// Create the texture atlas object.
		TextureAtlas(const std::string& filepath, uint32_t tileSize);

		// Returns the size of the atlas.
		sf::Vector2u GetSize() const { return m_Size; }

		// Returns a pointer to the texture atlas texture.
		const sf::Texture* GetTexture() const { return &m_Texture; }

		// Index layout.
		// [0] [1] [2]
		// [3] [4] [5]
		// [6] [7] [8]

		// Return texture coordinates of a texture with a given index counting from top left to bottom right.
		std::array<sf::Vector2f, 4> GetTextureCoordinates(uint32_t index);

		// Coordinate layout.
		// [0,0] [1,0] [2,0]
		// [0,1] [1,1] [2,1]
		// [0,2] [1,2] [2,2]

		// Returns the texture coordinates of a texture with a given coordinate.
		std::array<sf::Vector2f, 4> GetTextureCoordinates(const sf::Vector2u& coordinate);

	private:
		uint32_t m_TileSize;
		sf::Vector2u m_Size;
		sf::Texture m_Texture;
	};
}