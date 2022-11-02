// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#include "Tileset.h"

namespace Object
{
	TileSet::TileSet(const TileProperties& properties)
		: m_Properties(properties), m_Atlas(properties.TextureMap,
			properties.TextureMapTileSizeInPixels), m_LookupMap(properties.ColorReferenceMap, properties.ColorMap)
	{
		// Amount of quads to be rendered.
		uint32_t quadAmount = m_LookupMap.GetLookupMapSize().x * m_LookupMap.GetLookupMapSize().y;

		// Width of the tileset.
		uint32_t tilesetWidth = m_LookupMap.GetLookupMapSize().x;

		// Amount of vertices to be submitted.
		uint32_t vertAmount = quadAmount * 4;

		// Assign vertex array object.
		m_VertexArray = sf::VertexArray(sf::Quads, vertAmount);

		// Get tilesize.
		uint32_t tileSize = properties.TileSizeInGame;

		for (uint32_t i	 = 0; i < vertAmount - 4; i += 4)
		{
			// Value increments by 1 instead of 4.
			uint32_t singularIncrement = i * 0.25f;

			// Get vertex position values.
			uint32_t xPosition = (singularIncrement % tilesetWidth) * tileSize;
			uint32_t yPosition = (singularIncrement / tilesetWidth) * tileSize;


			// Get the texture index from the world color lookup table.
			uint32_t textureIndex = m_LookupMap.GetIndexData()[singularIncrement];


			// Write vertices to vertex array.
			std::array<sf::Vector2f, 4> texCoords = m_Atlas.GetTextureCoordinates(textureIndex);

			m_VertexArray[0 + i].position = sf::Vector2f(xPosition, yPosition);
			m_VertexArray[0 + i].texCoords = texCoords[0];

			m_VertexArray[1 + i].position = sf::Vector2f(xPosition + tileSize, yPosition);
			m_VertexArray[1 + i].texCoords = texCoords[1];

			m_VertexArray[2 + i].position = sf::Vector2f(xPosition + tileSize, yPosition + tileSize);
			m_VertexArray[2 + i].texCoords = texCoords[2];

			m_VertexArray[3 + i].position = sf::Vector2f(xPosition, yPosition + tileSize);
			m_VertexArray[3 + i].texCoords = texCoords[3];
		}
	}

}