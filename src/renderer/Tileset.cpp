// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#include "Tileset.h"

namespace Renderer
{
	TileSet::TileSet(const TileProperties& properties)
		: m_Properties(properties), m_Atlas(properties.TextureMap, properties.TextureMapTileSizeInPixels)
	{
		m_ColorToAtlasIndexLookupTable = LoadColorLookupTable(m_Properties);
		CreateVertexArray(m_Properties);
	}

	void TileSet::CreateVertexArray(const TileProperties& properties)
	{

		// Load world color map.
		sf::Image worldColorMap;
		if (!worldColorMap.loadFromFile(properties.ColorMap))
		{
			ASSERT(false, "Cannot load texture.");
		}


		// Get the ptr to the first color object.
		sf::Color* worldColorPtr = (sf::Color*)worldColorMap.getPixelsPtr();


		// Get the amount of pixels in the color lookup texture.
		uint32_t worldSize = worldColorMap.getSize().x * worldColorMap.getSize().y;


		// The amount of quads drawn.
		uint32_t quadAmount = worldSize * 4;


		// Get width of world texture in pixels.
		uint32_t worldWidth = worldColorMap.getSize().x;


		// Increment for position, used because the worldsize increments by 4 instead of 1 due to 4 vertices being written to per itteration.
		uint32_t positionIncrement = 0;


		// Assign vertex array object.
		m_VertexArray = sf::VertexArray(sf::Quads, quadAmount);

		for (uint32_t i = 0; i < quadAmount - 4; i += 4)
		{

			// Get vertex position values.
			uint32_t tileSize = properties.TileSizeInGame;
			uint32_t xPosition = (positionIncrement % worldWidth) * tileSize;
			uint32_t yPosition = (positionIncrement / worldWidth) * tileSize;
			
			positionIncrement++;


			// Get the texture index from the world color lookup table.
			uint32_t textureIndex = 0;
			for (uint32_t ti = 0; ti < m_ColorToAtlasIndexLookupTable.size(); ti++)
			{
				sf::Color worldColorAtPosition = *(worldColorPtr + positionIncrement);

				// Compare colors to current world color pixel and lookup table color.
				if (m_ColorToAtlasIndexLookupTable[ti].r == worldColorAtPosition.r &&
					m_ColorToAtlasIndexLookupTable[ti].g == worldColorAtPosition.g &&
					m_ColorToAtlasIndexLookupTable[ti].b == worldColorAtPosition.b)
				{
					textureIndex = ti;
					break;
				}
			}


			// Write vertices to vertex array.

			m_VertexArray[0 + i].position = sf::Vector2f((float)xPosition, (float)yPosition);
			m_VertexArray[0 + i].texCoords = m_Atlas.GetTextureCoordinates(textureIndex)[0];

			m_VertexArray[1 + i].position = sf::Vector2f((float)xPosition + tileSize, (float)yPosition);
			m_VertexArray[1 + i].texCoords = m_Atlas.GetTextureCoordinates(textureIndex)[1];

			m_VertexArray[2 + i].position = sf::Vector2f((float)xPosition + tileSize, (float)yPosition + tileSize);
			m_VertexArray[2 + i].texCoords = m_Atlas.GetTextureCoordinates(textureIndex)[2];

			m_VertexArray[3 + i].position = sf::Vector2f((float)xPosition, (float)yPosition + tileSize);
			m_VertexArray[3 + i].texCoords = m_Atlas.GetTextureCoordinates(textureIndex)[3];
		}
	}

	std::map<uint32_t, sf::Color> TileSet::LoadColorLookupTable(const TileProperties& properties)
	{

		// Load color reference texture.
		sf::Image colorReference;
		if (!colorReference.loadFromFile(properties.ColorReferenceMap))
		{
			ASSERT(false, "Cannot load texture.");
		}

		// Get the texture size.
		uint32_t colorReferenceSize = colorReference.getSize().x * colorReference.getSize().y;


		// Create lookup table.

		// Fill color ptr to the first element of pixel data.
		sf::Color* colorReferenceColorsPtr = (sf::Color*)colorReference.getPixelsPtr();

		std::map<uint32_t, sf::Color> colorAtlasLookupTable;

		// Write to the look up table. Every color refers to a Texture Atlas coordinate.
		for (uint32_t i = 0; i < colorReferenceSize; i++)
		{
			colorAtlasLookupTable[i] = *(colorReferenceColorsPtr + i);
		}

		return colorAtlasLookupTable;
	}
}