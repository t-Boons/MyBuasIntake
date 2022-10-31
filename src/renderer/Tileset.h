// Copyright (C) 2022 Tygo Boons
// All rights reserved.

/*	
	
	Usage:

	Recreate your texture atlas texture where the resolution is the amount of tiles that are in the atlas.
	Each tile requires its own color which the texture atlas will sample from.
	Create a 2nd texture that can be as big as you want and use the sampled colors from the color map to build your tiles.

	Example:
	-----------------------------------
	Texture Atlas texture = 256 x 256
	Texture Tile size in pixels = 64

	This means that the color map texture has to be:

	Color Map = 4 x 4
	-----------------------------------

*/

#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "core/core.h"
#include "textureatlas.h"

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

		// Create vertices from world color map.
		void CreateVertexArray(const TileProperties& properties);

		// Create lookup table for colors to texture atlas indexes.
		std::map<uint32_t, sf::Color> LoadColorLookupTable(const TileProperties& properties);

	private:
		TileProperties m_Properties;
		TextureAtlas m_Atlas;
		sf::VertexArray m_VertexArray;

		std::map<uint32_t, sf::Color> m_ColorToAtlasIndexLookupTable;



	};
}