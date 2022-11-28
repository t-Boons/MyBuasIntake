#pragma once

#include <SFML/Graphics.hpp>

namespace Renderer
{
	struct Mesh
	{
	public:
		Mesh(const sf::VertexArray& vertexArray)
			: m_Vertices(vertexArray)
		{}

		const sf::VertexArray& GetVertices() const { return m_Vertices; }

	private:
		sf::VertexArray m_Vertices;
	};
}