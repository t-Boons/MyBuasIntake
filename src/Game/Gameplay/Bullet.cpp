// 2022 Tygo Boons

#include "mypch.h"
#include "Bullet.h"

namespace Gameplay
{

	void Bullet::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();
		m_Hits = 0;
	}

	void Bullet::Update()
	{
		// Move forward.
		m_Transform->Translate(m_Transform->GetForward() * Core::Time::GetDeltaTime() * 25.0f);
	}

	void Bullet::OnCollisionEnter(RefPtr<Physics::Collision> collision)
	{
		// Reflect bullet off of the surface using the collision normal.
		m_Transform->SetRotation(glm::quatLookAt(glm::reflect(-m_Transform->GetForward(), collision->Normal), glm::vec3(0.0f, 1.0f, 0.0f)));
		LOG(collision->ObjectName)
		// Destroy bullet after X hits.
		if (++m_Hits >= RICOCHET_AMOUNT)
		{
			Parent->Destroy();
		}
	}
}