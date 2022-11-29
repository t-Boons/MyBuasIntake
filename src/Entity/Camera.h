// 2022 Tygo Boons

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
#include "Core/Core.h"

namespace Entity
{
	class Camera : public Component
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(Camera)

	public:
		Camera();

	public:
		// Return location, rotation and scale in one matrix.
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

	private:
		// Recalculates the transform matrix.
		void RecalculateProjectionMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		float m_Fov, m_Near, m_Far, m_Aspect;
	};
}