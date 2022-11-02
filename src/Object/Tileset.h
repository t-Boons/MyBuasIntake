// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Utils/TextureAtlas.h"
#include "Utils/ColorLookupMap.h"
#include "GameObject.h"

namespace Object
{
	struct TileProperties
	{
		std::string ColorReferenceMap;
		std::string TextureMap;
		std::string ColorMap;
		uint32_t TextureMapTileSizeInPixels;
		uint32_t TileSizeInGame;
	};

	class TileSet : public Object
	{
	public:
		// Construct tileset
		TileSet(const TileProperties& properties);

		// Return Texture atlas texture.	
		virtual const sf::Texture* GetTexture() const override { return m_Atlas.GetTexture(); }

	private:
		TileProperties m_Properties;
		Utils::TextureAtlas m_Atlas;
		Utils::ColorLookupMap m_LookupMap;
	};
}