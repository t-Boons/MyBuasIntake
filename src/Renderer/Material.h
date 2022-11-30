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

		// Static method to easily create material.
		static RefPtr<Material> Create(const RefPtr<Texture>& texture = nullptr, const RefPtr<Shader>& shader = nullptr)
		{
			return std::make_shared<Material>(texture, shader);
		}


		Material(const RefPtr<Texture>& texture, const RefPtr<Shader>& shader)
			: Texture(texture), Shader(shader)
		{}

		RefPtr<Texture> Texture;
		RefPtr<Shader> Shader;
	};
}