// 2022 Tygo Boons

#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include "Core/Core.h"

namespace Entity
{
	class Transform : public Component
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(Transform)

	public:
		Transform()
		{
			// Assign transform matrix by calculating.
			RecalculateTransformMatrix();
		}

	public:
		// Setters.
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateTransformMatrix(); }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation;  RecalculateTransformMatrix(); }
		void SetScale(const glm::vec3& scale) { m_LocalScale = scale;  RecalculateTransformMatrix(); }

		// Getters.
		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_LocalScale; }

		// Return location, rotation and scale in one matrix.
		const glm::mat4& GetTransformMatrix() const { return m_TransformMatrix; }

		// Movement.
		void Translate(const glm::vec3& translation) { m_Position += translation; RecalculateTransformMatrix(); }
		void Rotate(const glm::vec3& rotation) { m_Rotation += rotation; RecalculateTransformMatrix(); }

	private:
		// Recalculates the transform matrix.
		void RecalculateTransformMatrix();

	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_LocalScale = { 1.0f, 1.0f, 1.0f };

		glm::mat4 m_TransformMatrix = glm::mat4(1.0f);
	};
}