// 2022 Tygo Boons

#include "mypch.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/Game.h"

namespace Entity
{

	Camera::Camera()
	{
		SetPerspectiveProjection(70, 0.01f, 1000.0f);
		
		// Calculate aspect ratio by using window size.
		glm::vec2 screenSize = Core::Game::Get()->GetWindow()->GetResolution();
		float aspect = screenSize.x / screenSize.y;

		m_Aspect = aspect;

		// Update projection matrix.
		RecalculateProjectionMatrix();
		RecalculateViewProjectionMatrix();
	}

	void Camera::SetPerspectiveProjection(float fov, float znear, float zfar)
	{
		// Error checks
		if (fov < 0)
		{
			fov = 0;
			LOG_ERROR(GAMEOBJECT_IDENTITY + "Fov can not be lower than zero")
		}

		if (znear < 0.001f)
		{
			znear = 0.001f;
			LOG_ERROR(GAMEOBJECT_IDENTITY + "Z-Near can not be lower than 0.001f")
		}

		if (zfar < 0)
		{
			zfar = 0.001f;
			LOG_ERROR(GAMEOBJECT_IDENTITY + "Z-Far can not be lower than 0.001f")
		}

		// Set projection type.
		m_Projection = Projection::Perspective;

		// Update camera values.
		m_Fov = fov;
		m_Near = znear;
		m_Far = zfar;

		RecalculateProjectionMatrix();
	}

	void Camera::SetOrtographicProjection(float size, float znear, float zfar)
	{
		// Error checks.
		if (size < 0)
		{
			size = 0;
			LOG_ERROR(GAMEOBJECT_IDENTITY + "Size can not be lower than zero")
		}

		if (znear < 0.001f)
		{
			znear = 0.001f;
			LOG_ERROR(GAMEOBJECT_IDENTITY + "Z-Near can not be lower than 0.001f")
		}

		if (zfar < 0)
		{
			zfar = 0.001f;
			LOG_ERROR(GAMEOBJECT_IDENTITY + "Z-Far can not be lower than 0.001f")
		}

		// Set projection type.
		m_Projection = Projection::Ortographic;

		// Update camera values.
		m_Size = size;
		m_Near = znear;
		m_Far = zfar;

		RecalculateProjectionMatrix();
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
		switch (m_Projection)
		{
			case Projection::Perspective: m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far); break;
			case Projection::Ortographic: m_ProjectionMatrix = glm::ortho(-m_Size, m_Size * m_Aspect, -m_Size, m_Size / m_Aspect, m_Near, m_Far); break;
		}

	}

	const glm::vec3 Camera::GetViewForward() const
	{
		auto& a = m_ViewMatrix;
		return  glm::normalize(glm::vec3(a[0].z, a[1].z, a[2].z));
	}

	const glm::vec3 Camera::GetViewRight() const
	{
		auto& a = m_ViewMatrix;
		return glm::normalize(-glm::vec3(a[0].x, a[1].x, a[2].x));
	}

	const glm::vec3 Camera::GetViewUp() const
	{
		auto& a = m_ViewMatrix;
		return glm::normalize(-glm::vec3(a[0].y, a[1].y, a[2].y));
	}

}