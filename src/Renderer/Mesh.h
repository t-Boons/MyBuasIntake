#pragma once

#include <SFML/Graphics.hpp>
#include "glm/glm.hpp"
#include "VertexData.h"
#include <string>

namespace Renderer
{
	struct Mesh
	{
	public:

		MAKE_SHARED_ONEPARAM(Mesh, const std::string&, filepath)

		Mesh(const std::string& filepath);

		// Load mesh from file path.
		bool LoadMesh(const std::string& filePath);

		// Load mesh with raw data
		bool LoadMesh(const std::vector<float>& vertices, const std::vector<uint32_t> indices);

		// Get Vertex data.
		const RefPtr<VertexData>& GetVertexData() const { return m_VertexData; }

	private:
		RefPtr<VertexData> m_VertexData;
	};
}