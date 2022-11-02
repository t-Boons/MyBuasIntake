// Copyright (C) 2022 Tygo Boons
// All rights reserved.

#pragma once

#include <SFML/Graphics.hpp>

namespace Object
{

	//--------------------------------------------------------------//
	// Abstract Gameobject class to use for renderable game objects.//
	//--------------------------------------------------------------//

	class Object
	{
	public:
		// Return vertex array object.
		virtual const sf::VertexArray& GetVertexArray() const { return m_VertexArray; }

		// Return texture object.
		virtual const sf::Texture* GetTexture() const { return &m_Texture; }

		// Return viewport object. 
		virtual const sf::View* GetViewport() const { return nullptr; }

		// Virtual destructor to make sure Object's memory is free'd correctly.
		virtual ~Object() {}

	protected:
		sf::VertexArray m_VertexArray;
		sf::Texture m_Texture;
	};
}