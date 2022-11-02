// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "core/core.h"
#include "textureatlas.h"
#include "Utils/ColorLookupMap.h"

namespace Renderer
{
	struct TileProperties
	{
		std::string ColorReferenceMap;
		std::string TextureMap;
		std::string ColorMap;
		uint32_t TextureMapTileSizeInPixels;
		uint32_t TileSizeInGame;
	};

	class TileSet
	{
	public:
		// Construct tileset
		TileSet(const TileProperties& properties);

		// Return vertex array.
		const sf::VertexArray& GetVertexArray() { return m_VertexArray; }

		// Return Texture atlas texture.
		const sf::Texture* GetTexture() { return m_Atlas.GetTexture(); }

	private:


	private:
		TileProperties m_Properties;
		TextureAtlas m_Atlas;
		Utils::ColorLookupMap m_LookupMap;
		sf::VertexArray m_VertexArray;
	};
}