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
		// Set Object position..
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateTransformMatrix(); }

		// Set Object rotation in degrees.
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation;  RecalculateTransformMatrix(); }

		// Set Object scale.
		void SetScale(const glm::vec3& scale) { m_LocalScale = scale;  RecalculateTransformMatrix(); }

		// Get object position.
		const glm::vec3& GetPosition() const { return m_Position; }

		// Get Object rotation.
		const glm::vec3& GetRotation() const { return m_Rotation; }

		// Get Object scale.
		const glm::vec3& GetScale() const { return m_LocalScale; }

		// Get Forward vector.
		const glm::vec3& GetForward() const;

		// Get Up vector.
		const glm::vec3& GetUp() const;

		// Get Right vector.
		const glm::vec3& GetRight() const;
		
		// Return location, rotation and scale in one matrix.
		const glm::mat4& GetTransformMatrix() const { return m_TransformMatrix; }

		// Move Object in to direction.
		void Translate(const glm::vec3& translation) { m_Position += translation; RecalculateTransformMatrix(); }

		// Rotation Object.
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