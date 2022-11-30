// 2022 Tygo Boons

#pragma once

#include <SFML/Graphics.hpp>
#include "Core/core.h"

namespace Renderer
{
	class Texture
	{
	public:

		// Static method to easily create material.
		static RefPtr<Texture> Create(const std::string& filepath)
		{
			return std::make_shared<Renderer::Texture>(filepath);
		}

		Texture(const std::string& filepath);

		// Bind this texture to textureslot 0.
		void Bind();

	private:
		sf::Texture m_Texture;
	};
}