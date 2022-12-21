// 2022 Tygo Boons

#include "mypch.h"
#include "Bullet.h"
#include "TankMovement.h"

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
		m_Transform->Translate(m_Transform->GetForward() * Core::Time::GetDeltaTime() * BULLET_SPEED);
	}

	void Bullet::OnCollisionEnter(RefPtr<Physics::Collision> collision)
	{
		// Reflect bullet off of the surface using the collision normal.
		m_Transform->SetRotation(glm::quatLookAt(glm::reflect(-m_Transform->GetForward(), collision->Normal), glm::vec3(0.0f, 1.0f, 0.0f)));

		// Destroy bullet if it hits another bullet or tank.
		if (collision->HitObject->GetComponent<Gameplay::Bullet>() ||
			collision->HitObject->GetComponent<Gameplay::TankMovement>())
		{
			Parent->Destroy();
		}

		// Destroy bullet after RICOCHET_AMOUNT amount of hits hits.
		if (++m_Hits >= RICOCHET_AMOUNT)
		{
			Parent->Destroy();
		}
	}
}