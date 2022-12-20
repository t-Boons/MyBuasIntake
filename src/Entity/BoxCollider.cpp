// 2022 Tygo Boons

#include "mypch.h"

#include "BoxCollider.h"
#include "Core/Time.h"

namespace Entity
{
	void BoxCollider::Start()
	{
		m_Transform = GetComponent<Transform>();
	}

	void BoxCollider::Update()
	{
		// Update bounding box position.
		m_BoundingBox.SetPosition(m_Transform->GetPosition());

		// Update bounding box scale.
		m_BoundingBox.SetSize(m_Size);
	}

	RefPtr<Physics::Collision> BoxCollider::Intersects(const RefPtr<BoxCollider>& collider)
	{
		RefPtr<Physics::Collision> collisionEvent = m_BoundingBox.Intersects(collider->m_BoundingBox);

		// Set object name if collision found.
		if (collisionEvent)
		{
			collisionEvent->ThisObjectName = Parent->GetName();
		}

		return collisionEvent;
	}

	void BoxCollider::UpdateLastValidPosition()
	{
		m_LastValidPosition = m_Transform->GetPosition();
	}

	glm::vec3 BoxCollider::GetNormalFromLastValidPosition() const
	{
		// Calculate normalized vector between lastPosition and current position.
		glm::vec3 normal = glm::normalize(m_Transform->GetPosition() - m_LastValidPosition);

		// Set vector to 0 if normal is NAN.
		if (isnan(normal.x))
		{
			normal = { 0, 0, 0 };
		}

		return normal;
	}

	void BoxCollider::ResetToLastValidPosition()
	{
		m_Transform->SetPosition(m_LastValidPosition);
	}
}