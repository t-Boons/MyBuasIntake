// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Object
{
	class Skybox : public Object
	{
	public:
		// Construct skybox object.
		Skybox(const std::string& imageFilePath, const sf::Vector2u& windowSize);

		// Return fullscreen viewport for skybox.
		virtual const sf::View* GetViewport() const override { return &m_SkyboxView; }

	private:
		sf::View m_SkyboxView;
	};
}