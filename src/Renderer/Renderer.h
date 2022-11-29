// 2022 Tygo Boons

#pragma once

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Core/Game.h"
#include "Entity/GameObject.h"
#include "Entity/Camera.h"
#include "Entity/Transform.h"
#include "Renderer/Mesh.h"
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
		static void BeginScene(const Entity::Transform* transform, const Entity::Camera* camera);
		static void EndScene();

		static void SubmitMesh(const Mesh* mesh);

		static void Clear(const glm::vec3& color = { 0, 0, 0 });


	private:
		static RendererData s_Data;
	};
}