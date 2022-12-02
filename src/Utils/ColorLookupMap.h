// 2022 Tygo Boons

#pragma once

#include <SFML/Graphics.hpp>

namespace Utils
{
	class ColorLookupMap
	{
	public:
		ColorLookupMap(const std::string& colorReferenceMap, const std::string& colorUploadMap);

		const std::vector<uint32_t>& GetIndexData() const { return m_IndexData; }
		const sf::Vector2u GetLookupMapSize() const { return m_ColorUploadMap.getSize(); }

	private:
		std::map<uint32_t, sf::Color> m_ColorLookupTable;
		std::vector<uint32_t> m_IndexData;
		sf::Image m_ColorUploadMap;
		sf::Image m_ColorReferenceMap;
	};
}
