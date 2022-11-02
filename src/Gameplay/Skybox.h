// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Gameplay
{
	class Skybox : public GameObject
	{
	public:
		// Construct skybox object.
		Skybox(const std::string& imageFilePath, const sf::Vector2u& windowSize);

		// Return fullscreen view for skybox.
		sf::View GetView() const { return sf::View((sf::Vector2f)m_WindowSize * 0.5f,
														  (sf::Vector2f)m_WindowSize) ;}
	private:
		sf::Vector2u m_WindowSize;
	};
}