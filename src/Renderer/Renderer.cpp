// 2022 Tygo Boons

#include "mypch.h"
#include "Renderer.h"

namespace Renderer
{
	RendererData Renderer::s_Data = RendererData();

	void Renderer::Init()
	{
		// Initialize GLAD
		gladLoadGLLoader((GLADloadproc)(sf::Context::getFunction));

		// Pop SFML Opengl calls so they do not interfere.
		Core::Game::Get()->GetWindow()->popGLStates();

		// Set opengl settings.
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glDepthFunc(GL_LESS);
	}

	void Renderer::Renderer::BeginScene(const RefPtr<Entity::Camera> camera)
	{
		// Pop SFML Opengl calls so they do not interfere.
		Core::Game::Get()->GetWindow()->popGLStates();

		// Update view projection matrix.
		s_Data.m_ViewProjectionMatrix = camera->GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		// Apply the saved SFML Opengl calls.
		Core::Game::Get()->GetWindow()->pushGLStates();
	}

	void Renderer::SubmitMesh(const RefPtr<Entity::Transform>& transform, const RefPtr<Mesh> mesh, const RefPtr<Material> material)
	{
		// Bind vertex array with the data vertex layout.
		mesh->GetVertexData()->GetVertexArray()->Bind();

		// Bind shader and upload required matrices.
		material->Shader->Bind();
		material->Shader->UploadUniformMat4("uModel", transform->GetTransformMatrix());
		material->Shader->UploadUniformMat4("uViewProjection", s_Data.m_ViewProjectionMatrix);

		// Bind used texture.
		material->Texture->Bind();

		material->Shader->UploadUniformTextureSlot("uTexture", 0);

		// Get element count.
		uint32_t count = mesh->GetVertexData()->GetIndexBuffer()->GetElementCount();

		// Gl call to draw elements.
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::Clear(const glm::vec3& color)
	{
		// Clear depth and stencil buffer.
		glClearColor(color.r, color.g, color.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}