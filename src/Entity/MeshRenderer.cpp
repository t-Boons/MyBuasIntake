// 2022 Tygo Boons

#include "mypch.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Renderer/Renderer.h"

namespace Entity
{
	void MeshRenderer::Update()
	{
		// Render.
		Renderer::Renderer::SubmitMesh(GetComponent<Entity::Transform>(), m_Mesh, m_Material);
	}
}