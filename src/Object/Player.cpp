// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#include "Player.h"
#include "Core/Core.h"

namespace Object
{

	Player::Player(const std::string& playerTexture, float playerSize)
		: m_PlayerSize(playerSize)
	{
		// Load player texture.
		if (!m_Texture.loadFromFile(playerTexture))
		{
			ASSERT(false, "Unable to load texture");
		}

		// Create vertex array with a quad.
		m_VertexArray = sf::VertexArray(sf::Quads, 4);

		m_VertexArray[0].texCoords = sf::Vector2f(0.0f, 0.0f);
		m_VertexArray[1].texCoords = sf::Vector2f(m_Texture.getSize().x, 0.0f);

		m_VertexArray[2].texCoords = sf::Vector2f(m_Texture.getSize());

		m_VertexArray[3].texCoords = sf::Vector2f(0.0f, m_Texture.getSize().y);

	}

	void Player::Update(float deltaTime)
	{
		SetPosition(m_Position);
	}

	void Player::SetPosition(const sf::Vector2f& position)
	{
		// Set vertex position of all player vertices.
		m_VertexArray[0].position = sf::Vector2f(0.0f, 0.0f) + position;
		m_VertexArray[1].position = sf::Vector2f(m_PlayerSize, 0.0f) + position;
		m_VertexArray[2].position = sf::Vector2f(m_PlayerSize, m_PlayerSize) + position;
		m_VertexArray[3].position = sf::Vector2f(0.0f, m_PlayerSize) + position;
	}
}