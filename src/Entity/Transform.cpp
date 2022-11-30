// 2022 Tygo Boons

#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Entity
{
	void Transform::RecalculateTransformMatrix()
	{
		// Calculate location, rotation and scale matrix.
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_LocalScale);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
							glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
							glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(1.0f, 0.0f, 1.0f));

		// Multiply position, rotation and scale matrix.
		m_TransformMatrix = translate * rotation * scale;
	}

	const glm::vec3 Transform::GetForward() const
	{
		auto& a = m_TransformMatrix;
		return  glm::normalize(glm::vec3(a[0].z, a[1].z, a[2].z));
	}

	const glm::vec3 Transform::GetRight() const
	{
		auto& a = m_TransformMatrix;
		return glm::normalize(-glm::vec3(a[0].x, a[1].x, a[2].x));
	}

	const glm::vec3 Transform::GetUp() const
	{
		auto& a = m_TransformMatrix;
		return glm::normalize(-glm::vec3(a[0].y, a[1].y, a[2].y));
	}
}