// 2022 Tygo Boons

#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/Game.h"

Entity::Camera::Camera()
{
	// Initialize default values.
	m_Fov = 70;
	m_Near = 0.01f;
	m_Far = 1000;

	// Calculate aspect ratio by using window size.
	float aspect = Tmpl8::Game::GetWindow()->getSize().x / Tmpl8::Game::GetWindow()->getSize().y;
	m_Aspect = aspect;


	// Update projection matrix.
	RecalculateProjectionMatrix();
}

void Entity::Camera::RecalculateProjectionMatrix()
{
	// Calculate perspective matrix.
	m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
}
