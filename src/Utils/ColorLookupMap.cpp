// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#include "ColorLookupMap.h"
#include "Core/Core.h"

namespace Utils
{
	ColorLookupMap::ColorLookupMap(const std::string& colorReferenceMap, const std::string& colorUploadMap)
	{

		// Load color reference texture.
		if (!m_ColorReferenceMap.loadFromFile(colorReferenceMap))
		{
			ASSERT(false, "Cannot load texture.");
		}

		// Get the texture size.
		uint32_t colorReferenceSize = m_ColorReferenceMap.getSize().x * m_ColorReferenceMap.getSize().y;

		// Fill color ptr to the first element of pixel data.
		sf::Color* colorReferenceColorsPtr = (sf::Color*)m_ColorReferenceMap.getPixelsPtr();

		// Write to the look up table. Every color refers to a Texture Atlas coordinate.
		for (uint32_t i = 0; i < colorReferenceSize; i++)
		{
			m_ColorLookupTable[i] = colorReferenceColorsPtr[i];
		}



		// Load color upload map.
		if (!m_ColorUploadMap.loadFromFile(colorUploadMap))
		{
			ASSERT(false, "Cannot load texture.");
		}


		// Get the ptr to the first color object.
		sf::Color* uploadColorPtr = (sf::Color*)m_ColorUploadMap.getPixelsPtr();


		// Get the amount of pixels in the color lookup texture.
		uint32_t uploadColorSize = m_ColorUploadMap.getSize().x * m_ColorUploadMap.getSize().y;

		// Resize vector to make it able to accomodate the 
		m_IndexData.resize(uploadColorSize);

		for (size_t i = 0; i < uploadColorSize; i++)
		{
			for (uint32_t ti = 0; ti < m_ColorLookupTable.size(); ti++)
			{
				sf::Color worldColorAtPosition = uploadColorPtr[i];

				// Compare colors to current world color pixel and lookup table color.
				if (m_ColorLookupTable[ti] == worldColorAtPosition)
				{
					m_IndexData[i] = ti;
					break;
				}
			}
		}
	}
}