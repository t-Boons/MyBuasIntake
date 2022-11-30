// 2022 Tygo Boons

#pragma once

#include <SFML/Graphics.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Core/Core.h"

namespace Renderer
{
	struct Material
	{
	public:

		MAKE_SHARED_TWOPARAM(Material, const RefPtr<Texture>&, texture, const RefPtr<Shader>&, shader)

		Material(const RefPtr<Texture>& texture, const RefPtr<Shader>& shader)
			: Texture(texture), Shader(shader)
		{}

		RefPtr<Texture> Texture;
		RefPtr<Shader> Shader;
	};
}