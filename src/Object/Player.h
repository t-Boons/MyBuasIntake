// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Object
{
	class Player : public Object
	{
	public:
		// Construct player object.
		Player(const std::string& playerTexture, float playerSize = 32);

		// Update player.
		virtual void Update(float deltaTime) override;

		// Set the player positino in pixel space.
		void SetPosition(const sf::Vector2f& sposition);

	private:
		sf::Vector2f m_Position;
		float m_PlayerSize;
	};
}