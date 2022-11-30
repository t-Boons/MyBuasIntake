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
		// Set Object position..
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewProjectionMatrix(); }

		// Set Object rotation in degrees.
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation;  RecalculateViewProjectionMatrix(); }

		// Get object position.
		const glm::vec3& GetPosition() const { return m_Position; }

		// Get Object rotation.
		const glm::vec3& GetRotation() const { return m_Rotation; }

		// Get Forward vector.
		const glm::vec3& GetForward() const;

		// Get Up vector.
		const glm::vec3& GetUp() const;

		// Get Right vector.
		const glm::vec3& GetRight() const;

		// Move Object in to direction.
		void Translate(const glm::vec3& translation) { m_Position += translation; RecalculateViewProjectionMatrix(); }

		// Rotation Object.
		void Rotate(const glm::vec3& rotation) { m_Rotation += rotation; RecalculateViewProjectionMatrix(); }

		// Return Camera matrix.
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		// Recalculates the transform matrix.
		void RecalculateProjectionMatrix();
		void RecalculateViewProjectionMatrix();

	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		float m_Fov, m_Near, m_Far, m_Aspect;
	};
}