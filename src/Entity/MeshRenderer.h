// 2022 Tygo Boons

#pragma once

#include "Component.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"

namespace Entity
{
	class MeshRenderer : public Component
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(MeshRenderer)

	public:

		virtual void Update() override;

		// Set mesh object.
		void SetMesh(const RefPtr<Renderer::Mesh>& mesh) { m_Mesh = mesh; }

		// Set material object.
		void SetMaterial(const RefPtr<Renderer::Material>& material) { m_Material = material; }

		// Get mesh object.
		const RefPtr<Renderer::Mesh> GetMesh() const { return m_Mesh; }

		// Get

	private:
		RefPtr<Renderer::Mesh> m_Mesh;
		RefPtr<Renderer::Material> m_Material;
	};
}