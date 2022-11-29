// 2022 Tygo Boons

#pragma once

#include <SFML/Graphics.hpp>
#include "Shader.h"

namespace Renderer
{
	struct Material
	{
	public:
		Material()
			: Texture(new sf::Texture), Shader(nullptr)
		{}

		sf::Texture* Texture;
		Shader* Shader;
	};
}