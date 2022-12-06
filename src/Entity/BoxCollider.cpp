// 2022 Tygo Boons

#include "mypch.h"

#include "BoxCollider.h"

namespace Entity
{
	void BoxCollider::Start()
	{
		m_Transform = Parent->GetComponent<Transform>();
	}

	void BoxCollider::Update()
	{
		// Update bounding box position.
		m_BoundingBox.SetPosition(m_Transform->GetPosition());

		// Update bounding box scale.
		m_BoundingBox.SetSize(m_Transform->GetScale());
	}

	void BoxCollider::TryCollision(const RefPtr<BoxCollider>& collider)
	{
		// See if collider intersects this one.
		bool intersects = Intersects(collider);

		if (intersects)
		{
			// Calculate collision hit normal.
			m_Transform->SetPosition(m_LastValidPosition);
		}

		// Update old position to position this frame.
		m_LastValidPosition = m_Transform->GetPosition();
	}
}