// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#pragma once

#include <SFML/Graphics.hpp>

namespace Gameplay
{
	//
	// Abstract gameObject class 
	//

	class GameObject
	{
	public:
		virtual const sf::VertexArray& GetVertexArray() const { return m_VertexArray; }
		virtual const sf::Texture* GetTexture() const { return &m_Texture; }

	protected:
		sf::VertexArray m_VertexArray;
		sf::Texture m_Texture;
	};
}