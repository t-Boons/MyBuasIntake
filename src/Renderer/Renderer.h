// 2022 Tygo Boons

#pragma once

#include "glad/glad.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Core/Game.h"
#include "Entity/Camera.h"
#include "Entity/Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "glm/glm.hpp"

namespace Renderer
{
	struct RendererData
	{
		glm::mat4 m_ViewProjectionMatrix;
	};

	class Renderer
	{
	public:

		// Initialize the renderer.
		static void Init();

		// Begin the scene drawing.
		static void BeginScene(const RefPtr<Entity::Camera> camera);
		
		// End scene drawing.
		static void EndScene();

		// Draw mesh.
		static void SubmitMesh(const RefPtr<Entity::Transform>& transform, const RefPtr<Mesh> mesh, const RefPtr<Material> material);

		// Clear render buffer..
		static void Clear(const glm::vec3& color = { 0, 0, 0 });



	private:
		static RendererData s_Data;
	};
}