// 2022 Tygo Boons

#pragma once

#include <SFML/Graphics.hpp>
#include "Core/core.h"

namespace Renderer
{
	class Texture
	{
	public:

		MAKE_SHARED_ONEPARAM(Texture, const std::string&, filepath)

		Texture(const std::string& filepath);

		// Bind this texture to textureslot 0.
		void Bind();

	private:
		sf::Texture m_Texture;
	};
}