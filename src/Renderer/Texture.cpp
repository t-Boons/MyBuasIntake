// 2022 Tygo Boons

#include "mypch.h"
#include "Texture.h"

namespace Renderer
{
	Texture::Texture(const std::string& filepath)
	{
		// Initialize texture.
		m_Texture = sf::Texture();

		// Load texture from file.
		m_Texture.loadFromFile(filepath);
	}

	void Texture::Bind()
	{
		// Bind texture to textureslot 0.
		sf::Texture::bind(&m_Texture, sf::Texture::Normalized);
	}
}