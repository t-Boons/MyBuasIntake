// 2022 Tygo Boons

#include "mypch.h"

#include "TankGun.h"

namespace Gameplay
{
	void TankGun::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();

		// Get tank input component from parent object (because the tank body object contains the tankinput component)
		m_Input = m_ParentTransform->GetComponent<TankInput>();

		
		// Get bullet prefab to copy from.
		m_BulletPrefab = ScenePrefabs::CreateBullet();

		m_BulletsInChamber = CONSECUTIVE_BULLET_COUNT;
	}

	void TankGun::Update()
	{
		// Set position equal to tank body position.
		if (m_ParentTransform)
		{
			m_Transform->SetPosition(m_ParentTransform->GetPosition());
		}

		// Update the gun's rotation.
		if (m_Input)
		{
			SetGunRotation(m_Input->GetGunDirectionInput());
		}

		// See if mouse button is pressed and shoot if it is.
		if (m_Input && m_Input->IsShooting())
		{
			if (HasAmmo())
			{
				Shoot();

				// Reload the gun if it isn't already reloading.
				Reload();
			}
		}
	}

	void TankGun::SetGunRotation(const glm::vec2& direction)
	{
		// Calculate the angle based on the look direction.
		float angle = glm::acos(glm::dot(glm::vec2(0.0f, 1.0f), direction));
		angle = direction.x > 0 ? -angle : angle;

		// Rotate turret to right direction.
		m_Transform->SetRotation(glm::quat({ 0, angle + glm::radians(90.0f), 0 }));
	}

	void TankGun::Shoot()
	{
		// Reduce bullet count. 
		m_BulletsInChamber--;

		// Spawn bullet.
		Entity::GameObject::Instantiate(m_BulletPrefab,
			m_Transform->GetPosition() + m_Transform->GetForward() * 2.0f + glm::vec3(0.0f, 1.0f, 0.0f),
			m_Transform->GetRotation());
	}

	bool TankGun::HasAmmo()
	{
		return m_BulletsInChamber > 0;
	}

	void TankGun::Reload()
	{
		if (!m_Reloaded)
		{
			m_Reloaded = true;

			// Start a thread that resets the bullet count after x amount of seconds.
			m_RefilBulletThread = std::thread([=]()
				{
					Sleep(BULLET_REFIL_DELAY);
					m_BulletsInChamber = CONSECUTIVE_BULLET_COUNT;
					m_Reloaded = false;
				});

			// Detach the thread so it runs whilst not having to be joined.
			m_RefilBulletThread.detach();
		}
	}
}