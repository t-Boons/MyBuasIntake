// 2022 Tygo Boons

#include "mypch.h"

#include "BoxCollider.h"
#include "Core/Time.h"

namespace Entity
{
	void BoxCollider::UpdateScaleAndPosition()
	{
		// Update bounding box position.
		m_BoundingBox.SetPosition(m_Transform->GetPosition());

		// Update bounding box scale.
		m_BoundingBox.SetSize(m_Transform->GetScale());
	}

	void BoxCollider::Start()
	{
		m_Transform = Parent->GetComponent<Transform>();
	}

	void BoxCollider::Update()
	{
		UpdateScaleAndPosition();
	}

	void BoxCollider::UpdateLastValidPosition()
	{
		m_LastValidPosition = m_Transform->GetPosition();
	}
	void BoxCollider::ResetToLastValidPosition()
	{
		m_Transform->SetPosition(m_LastValidPosition);
	}
}