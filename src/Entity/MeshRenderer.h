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

		// Set mesh object.
		void SetMesh(RefPtr<Renderer::Mesh> mesh) { m_Mesh = mesh; }

		// Get mesh object.
		const RefPtr<Renderer::Mesh> GetMesh() const { return m_Mesh; }

	private:
		RefPtr<Renderer::Mesh> m_Mesh;
	};
}