// 2022 Tygo Boons

#include "mypch.h"
#include "Bullet.h"
#include "TankEngine.h"

namespace Gameplay
{
	void Bullet::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();

		// Get multiple audiosource components.
		m_Clack = GetComponents<Entity::AudioSource>()[0];
		m_Thud = GetComponents<Entity::AudioSource>()[1];

		m_Hits = 0;
		m_DelayTime = 0;
	}

	void Bullet::Update()
	{
		if (!m_DeleteDelayStarted)
		{
			// Move forward.
			m_Transform->Translate(m_Transform->GetForward() * Core::Time::GetDeltaTime() * BULLET_SPEED);
		}
		else
		{
			// Update delay time.
			m_DelayTime += Core::Time::GetDeltaTime();

			// Destroy object after DESTROY_DELAY amount of time.
			if (m_DelayTime > DESTROY_DELAY)
			{
				Parent->Destroy();
			}
		}
	}

	void Bullet::OnCollisionEnter(RefPtr<Physics::Collision> collision)
	{
		// Only run this if object is not being deleted.
		if (!m_DeleteDelayStarted)
		{
			// Reflect bullet off of the surface using the collision normal.
			m_Transform->SetRotation(glm::quatLookAt(glm::reflect(-m_Transform->GetForward(), collision->Normal), glm::vec3(0.0f, 1.0f, 0.0f)));

			// Log hit.
			LOG_INFO(GAMEOBJECT_IDENTITY + "Hit: " + collision->HitObject->GetName() + " ID: " + STR(collision->HitObject->GetID()))

			// Check if bullet should be destroyed.
			bool destroyDueTohitCount = ++m_Hits >= RICOCHET_AMOUNT;
			bool destroyDueToCollision = collision->HitObject->GetComponent<Gameplay::Bullet>() || collision->HitObject->GetComponent<Gameplay::TankEngine>();

			if (destroyDueTohitCount || destroyDueToCollision)
			{
				m_DeleteDelayStarted = true;
				m_Thud->Play();
			}
			else
			{
				// Play clack sound.
				m_Clack->SetPitch((rand() % 250) / 1000.0f + 0.95f);
				m_Clack->Play();
			}
		}
	}
}