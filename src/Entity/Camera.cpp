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
	sf::Vector2f screenSize = (sf::Vector2f)Tmpl8::Game::Get()->GetWindow()->getSize();
	float aspect = screenSize.x / screenSize.y;
	m_Aspect = aspect;


	// Update projection matrix.
	RecalculateProjectionMatrix();
}

void Entity::Camera::RecalculateProjectionMatrix()
{
	// Calculate perspective matrix.
	m_ProjectionMatrix = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
}
