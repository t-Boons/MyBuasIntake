// 2022 Tygo Boons

#include "mypch.h"
#include "Bullet.h"
#include "TankEngine.h"

namespace Gameplay
{
	void Bullet::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();

		// Add all required audio sources.
		m_Clack = AddComponent(Entity::AudioSource::Create());
		m_Clack->LoadClipFromFile("Assets/Audio/Effects/Clack.wav");
		m_Clack->SetVolume(0.5f);

		m_Thud = AddComponent(Entity::AudioSource::Create());
		m_Thud->LoadClipFromFile("Assets/Audio/Effects/Thud.wav");
		m_Thud->SetVolume(0.5f);
		m_Thud->SetPitch(0.75f);

		m_Hits = 0;
		m_Destroyed = false;
	}

	void Bullet::Update()
	{
		// Ignore movement if object is queued to be deleted.
		if (m_Destroyed)
		{
			return;
		}

		// Move forward.
		m_Transform->Translate(m_Transform->GetForward() * Core::Time::GetDeltaTime() * BULLET_SPEED);
	}

	void Bullet::OnCollisionEnter(RefPtr<Physics::Collision> collision)
	{
		// Ignore any collision if this object is queued to be destroyed.
		if (m_Destroyed)
		{
			return;
		}

		// Reflect bullet off of the surface using the collision normal.
		m_Transform->SetRotation(glm::quatLookAt(glm::reflect(-m_Transform->GetForward(), collision->Normal), glm::vec3(0.0f, 1.0f, 0.0f)));

		// Log hit.
		LOG_INFO(GAMEOBJECT_IDENTITY + "Hit: " + collision->HitObject->GetName() + " ID: " + STR(collision->HitObject->GetID()))

		// Check if bullet should be destroyed.
		bool destroyDueTohitCount = ++m_Hits >= RICOCHET_AMOUNT;
		bool destroyDueToCollision = collision->HitObject->GetComponent<Gameplay::Bullet>() || collision->HitObject->GetComponent<Gameplay::TankEngine>();

		if (destroyDueTohitCount || destroyDueToCollision)
		{
			// Play thud sound.
			m_Thud->Play();

			// Remove the mesh renderer.
			GetComponent<Entity::MeshRenderer>()->Destroy();

			// Run deletion event
			Utils::TimedEvent(DESTROY_DELAY, this, [&]() {Parent->Destroy(); });

			m_Destroyed = true;
		}
		else
		{
			// Play clack sound.
			m_Clack->SetPitch(Utils::Random::Range(0.75f, 1.2f));
			m_Clack->Play();
		}
	}
}