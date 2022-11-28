// 2022 Tygo Boons

#pragma once

#include "Component.h"
#include "Renderer/Mesh.h"

namespace Entity
{
	class MeshRenderer : public Component
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(MeshRenderer)

	public:
		// Load mesh in .obj format.
		void LoadMesh(const std::string& filepath);

		// Get mesh object.
		const Renderer::Mesh& GetMesh() const { return m_Mesh; }

	private:
		Renderer::Mesh m_Mesh;
	}
}