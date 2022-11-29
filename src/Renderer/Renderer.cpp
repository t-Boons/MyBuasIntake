// 2022 Tygo Boons

#include "Renderer.h"

using namespace Tmpl8;

namespace Renderer
{
	RendererData Renderer::s_Data = RendererData();

	void Renderer::Renderer::BeginScene(const Entity::Transform* transform, const Entity::Camera* camera)
	{
		// Update view projection matrix.
		s_Data.m_ViewProjectionMatrix = transform->GetTransformMatrix() * camera->GetProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::SubmitMesh(const Mesh* mesh)
	{
		sf::CircleShape shape = sf::CircleShape(50);
		Game::GetWindow()->draw(shape);
	}

	void Renderer::Renderer::Clear(const glm::vec3& color)
	{
		// Clear depth and stencil buffer.
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearColor(color.r, color.g, color.b, 1.0f);
	}
}