// 2022 Tygo Boons

#include "mypch.h"
#include "Transform.h"

namespace Entity
{
	void Transform::RecalculateTransformMatrix()
	{
		// Calculate location, rotation and scale matrix.
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_LocalScale);
		glm::mat4 rotation = glm::toMat4(m_Rotation);

		// Multiply position, rotation and scale matrix.
		m_TransformMatrix = translate * rotation * scale;
	}

	glm::vec3 Transform::GetForward() const
	{
		auto& a = m_TransformMatrix;
		return  glm::normalize(glm::vec3(a[2].x, a[1].x, a[0].x));
	}

	glm::vec3 Transform::GetRight() const
	{
		auto& a = m_TransformMatrix;
		return  glm::normalize(glm::vec3(a[2].z, a[1].z, a[0].z));
	}

	glm::vec3 Transform::GetUp() const
	{
		auto& a = m_TransformMatrix;
		return  glm::normalize(glm::vec3(a[2].y, a[1].y, a[0].y));
	}
}