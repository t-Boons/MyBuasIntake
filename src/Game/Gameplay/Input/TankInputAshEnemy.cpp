// 2023 Tygo Boons

#include "mypch.h"

#include "TankInputAshEnemy.h"

namespace Gameplay
{
	void TankInputAshEnemy::StartInput()
	{
		StartShootInput();
		StartMovementInput();
		StartGunDirectionInput();
	}

	void TankInputAshEnemy::UpdateInput()
	{
		UpdatePlayerSpotted();
		UpdateGunToPlayerDirection();
		UpdateGunMovementInterpolation();
	}

	void TankInputAshEnemy::StartShootInput()
	{
		// Create timed event to shoot the gun;
		Utils::TimedEvent e(Utils::Random::Range(0.0f, RANDOM_SHOOT_MAX_DELAY), [=]()
			{
				// Send a shot input.
				if (m_PlayerSpotted)
				{
					Shoot();
				}

				StartShootInput();
			});
	}

	void TankInputAshEnemy::StartMovementInput()
	{
		// Randomized movement input.
		m_MovementInput.x = Utils::Random::Range(-1.0f, 1.0f);
		m_MovementInput.y = Utils::Random::Range(-1.0f, 1.0f);
		m_MovementInput = glm::normalize(m_MovementInput) * MOVEMENT_SPEED_MULTIPLIER;

		// Create timed event to move the tank;
		Utils::TimedEvent e(Utils::Random::Range(0.0f, RANDOM_DIRECTION_MAX_DELAY), [=]()
			{
				StartMovementInput();
			});
	}

	void TankInputAshEnemy::StartGunDirectionInput()
	{
		// If the player tank is spotted move the gun barrel to the player tank.
		if (m_PlayerSpotted && Utils::Random::Chance(0.85f))
		{
			LockOnToPlayer(true);
		}
		else
		{
			// Make tank gun look random direction.
			m_NewGunInput.x = Utils::Random::Range(-1.0f, 1.0f);
			m_NewGunInput.y = Utils::Random::Range(-1.0f, 1.0f);
			m_NewGunInput = glm::normalize(m_NewGunInput);
			LockOnToPlayer(false);
		}

		Utils::TimedEvent e(Utils::Random::Range(0.0f, RANDOM_GUN_DIRECTION_MAX_DELAY), [=]()
			{
				StartGunDirectionInput();
			});
	}

	void TankInputAshEnemy::UpdateGunToPlayerDirection()
	{
		m_GunToPlayerDirection = glm::normalize(Entity::GameObject::Find("PlayerTank")->GetComponent<Entity::Transform>()->GetPosition() - GetComponent<Entity::Transform>()->GetPosition());
	}

	void TankInputAshEnemy::UpdatePlayerSpotted()
	{
		// Get current position.
		glm::vec3 origin = GetComponent<Entity::Transform>()->GetPosition();

		// Shoot a raycast in the direction of the tank to see if this tank can see it.
		RefPtr<Physics::RaycastHit> hit = Physics::Physics::RayCast(origin + m_GunToPlayerDirection * 2.0f, m_GunToPlayerDirection, 1000);

		m_PlayerSpotted = hit && hit->HitObject->GetName() == "PlayerTank";
	}

	void TankInputAshEnemy::UpdateGunMovementInterpolation()
	{
		// Smoothly interpolate gun input to new input if inputs are different.
		m_GunInput = glm::mix(m_GunInput, m_NewGunInput, Core::Time::GetDeltaTime() * 2.5f);
	}

	void TankInputAshEnemy::LockOnToPlayer(bool lock)
	{
		m_LockedOnPlayer = lock;

		if (m_LockedOnPlayer)
		{
			Utils::TimedEvent e(Utils::Random::Range(0.0f, 0.1f), [=]()
				{
					// Set the new gun input to the player direction.
					m_NewGunInput = glm::normalize(glm::vec2(m_GunToPlayerDirection.z, m_GunToPlayerDirection.x));
					LockOnToPlayer(m_LockedOnPlayer);
				});
		}
	}
}