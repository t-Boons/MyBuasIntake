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

		auto obj = GameObject::Find("Cube1");
		if (obj->GetName() != Parent->GetName())
		{
			auto collision = obj->GetComponent<Entity::BoxCollider>()->m_BoundingBox.Intersects(m_BoundingBox);
			if (collision)
			{
				m_Transform->SetPosition(m_OldPosition);
			}
		}

		m_OldPosition = m_Transform->GetPosition();
	}
}