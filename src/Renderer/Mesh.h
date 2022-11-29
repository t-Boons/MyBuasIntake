#pragma once

#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"

namespace Renderer
{
	#define VERTEX_SIZE 8

	struct Mesh
	{
	public:
		Mesh();

		// Load mesh from file path.
		bool LoadMesh(const std::string& filePath);

		// Load mesh with raw data
		bool LoadMesh(const float* vertices, uint32_t size);

	public:
		std::vector<glm::vec3> Position;
		std::vector<glm::vec2> TexCoordinate;
		std::vector<glm::vec3> Normal;
		std::vector<uint32_t> Indices;
	};
}