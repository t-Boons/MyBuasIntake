// 2022 Tygo Boons

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/Game.h"

namespace Entity
{

	Entity::Camera::Camera()
	{
		// Initialize default values.
		m_Fov = 70;
		m_Near = 0.01f;
		m_Far = 1000.0f;

		// Calculate aspect ratio by using window size.
		sf::Vector2f screenSize = (sf::Vector2f)Tmpl8::Game::Get()->GetWindow()->getSize();
		float aspect = screenSize.x / screenSize.y;
		m_Aspect = aspect;


		// Update projection matrix.
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void Camera::RecalculateViewProjectionMatrix()
	{
		// Calculate location, rotation and scale matrix.
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 rotation = 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(1.0f, 0.0f, 1.0f));

		// Set view matrix value.
		m_ViewMatrix = glm::inverse(translate * rotation);

		// Multiply position, rotation and scale matrix.
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Entity::Camera::RecalculateProjectionMatrix()
	{
		// Calculate perspective matrix.
		m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
	}

	const glm::vec3& Camera::GetForward() const
	{
		auto& a = m_ViewMatrix;
		return  glm::normalize(glm::vec3(a[0].z, a[1].z, a[2].z));
	}

	const glm::vec3& Camera::GetRight() const
	{
		auto& a = m_ViewMatrix;
		return glm::normalize(-glm::vec3(a[0].x, a[1].x, a[2].x));
	}

	const glm::vec3& Camera::GetUp() const
	{
		auto& a = m_ViewMatrix;
		return glm::normalize(-glm::vec3(a[0].y, a[1].y, a[2].y));
	}

}