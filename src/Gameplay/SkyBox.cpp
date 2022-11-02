// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#include "Skybox.h"

namespace Gameplay
{
	Skybox::Skybox(const std::string& imageFilePath, const sf::Vector2u& windowSize)
		: m_WindowSize(windowSize)
	{
		// Load skybox texture.
		m_Texture.loadFromFile(imageFilePath);

		// Create skybox vertex array object.
		m_VertexArray = sf::VertexArray(sf::Quads, 4);

		// Assign vertex array object vertices.
		m_VertexArray[0] = sf::Vertex({ 0.0f, 0.0f }								, { 0.0f, 0.0f });
		m_VertexArray[1] = sf::Vertex({ 0.0f, (float)windowSize.y }				, { 0.0f, (float)m_Texture.getSize().y});
		m_VertexArray[2] = sf::Vertex({ (float)windowSize.x, (float)windowSize.y },  { (float)m_Texture.getSize().x, (float)m_Texture.getSize().y});
		m_VertexArray[3] = sf::Vertex({ (float)windowSize.x, 0.0f }				, { (float)m_Texture.getSize().x, 0.0f });

	}
}