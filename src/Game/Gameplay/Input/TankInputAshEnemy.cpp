// 2023 Tygo Boons

#include "mypch.h"

#include "TankInputAshEnemy.h"
#include "Game/Gameplay/TankEngine.h"

namespace Gameplay
{
	void TankInputAshEnemy::StartInput()
	{
		// Get gun transform reference.
		m_GunTransform = GetComponent<TankEngine>()->GetGunObject()->GetComponent<Entity::Transform>();

		StartShootInput();
		StartMovementInput();
		StartGunDirectionInput();
	}

	void TankInputAshEnemy::UpdateInput()
	{
		UpdateGunToPlayerDirection();
		UpdateGunMovementInterpolation();
		UpdateWallCorrectionMovement();
	}

	void TankInputAshEnemy::StartShootInput()
	{
		// Create timed event to shoot the gun;
		Utils::TimedEvent e(Utils::Random::Range(0.0f, RANDOM_SHOOT_MAX_DELAY), this, [&]()
			{
				// Send a shot input.
				if (IsPlayerSpotted() && !IsAimingAtEnemy())
				{
					Shoot();
				}

				StartShootInput();
			});
	}

	void TankInputAshEnemy::StartMovementInput()
	{
		RandomizeMovementInput();

		// Create timed event to move the tank;
		Utils::TimedEvent e(Utils::Random::Range(0.0f, RANDOM_DIRECTION_MAX_DELAY), this, [&]()
			{
				StartMovementInput();
			});
	}

	void TankInputAshEnemy::StartGunDirectionInput()
	{
		// If the player tank is spotted move the gun barrel to the player tank.
		if (IsPlayerSpotted())
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

		Utils::TimedEvent e(Utils::Random::Range(0.0f, RANDOM_GUN_DIRECTION_MAX_DELAY), this, [&]()
			{
				StartGunDirectionInput();
			});
	}

	void TankInputAshEnemy::UpdateGunToPlayerDirection()
	{
		RefPtr<Entity::GameObject> player = Entity::GameObject::Find("PlayerTank");

		if (player)
		{
			m_GunToPlayerDirection = glm::normalize(player->GetComponent<Entity::Transform>()->GetPosition() - GetComponent<Entity::Transform>()->GetPosition());
		}
	}

	bool TankInputAshEnemy::IsPlayerSpotted()
	{
		// Get current position.
		glm::vec3 origin = GetComponent<Entity::Transform>()->GetPosition();

		// Shoot a raycast in the direction of the tank to see if this tank can see it.
		RefPtr<Physics::RaycastHit> hit = Physics::Physics::RayCast(origin + m_GunToPlayerDirection * 2.0f, m_GunToPlayerDirection, 1000);

		return hit && hit->HitObject->GetName() == "PlayerTank";
	}

	void TankInputAshEnemy::UpdateGunMovementInterpolation()
	{
		// Smoothly interpolate gun input to new input if inputs are different.
		m_GunInput = glm::mix(m_GunInput, m_NewGunInput, Core::Time::GetDeltaTime() * 3.0f);
	}

	void TankInputAshEnemy::LockOnToPlayer(bool lock)
	{
		m_LockedOnPlayer = lock;

		if (m_LockedOnPlayer)
		{
			Utils::TimedEvent e(0.1f, this, [=]()
				{
					// Set the new gun input to the player direction.
					m_NewGunInput = glm::normalize(glm::vec2(m_GunToPlayerDirection.z, m_GunToPlayerDirection.x));
					LockOnToPlayer(m_LockedOnPlayer);
				});
		}
	}

	void TankInputAshEnemy::RandomizeMovementInput()
	{
		// Randomized movement input.
		m_MovementInput.x = Utils::Random::Range(-0.5, 1.0f);
		m_MovementInput.y = Utils::Random::Range(-0.5f, 0.5f);
		m_MovementInput = glm::normalize(m_MovementInput) * MOVEMENT_SPEED_MULTIPLIER;
	}

	void TankInputAshEnemy::UpdateWallCorrectionMovement()
	{
		// Get transform component.
		RefPtr<Entity::Transform> transform = GetComponent<Entity::Transform>();

		// Get forward and back raycast hit objects.
		RefPtr<Physics::RaycastHit> forwardHit = Physics::Physics::RayCast(transform->GetPosition() + transform->GetForward() * 2.0f, transform->GetForward(), 1000);
		RefPtr<Physics::RaycastHit> backHit = Physics::Physics::RayCast(transform->GetPosition() + -transform->GetForward() * 2.0f, -transform->GetForward(), 1000);

		// Don't do anything if both disatnces are below 3
		if (forwardHit && forwardHit->Distance < MINIMUM_TANK_WALL_DISTANCE &&
			backHit && backHit->Distance < MINIMUM_TANK_WALL_DISTANCE)
		{
			return;
		}

		// If the move can is too close forward or backwards to a wall run this.
		if (forwardHit && forwardHit->Distance < MINIMUM_TANK_WALL_DISTANCE ||
			backHit && backHit->Distance < MINIMUM_TANK_WALL_DISTANCE)
		{
			// Get hit objects from left and right.
			RefPtr<Physics::RaycastHit> leftHit = Physics::Physics::RayCast(transform->GetPosition() + -transform->GetRight() * 2.0f, -transform->GetRight(), 1000);
			RefPtr<Physics::RaycastHit> rightHit = Physics::Physics::RayCast(transform->GetPosition() + transform->GetRight() * 2.0f, transform->GetRight(), 1000);

			// Get distances to objects from all directions.
			float leftDistance = leftHit ? leftHit->Distance : INFINITY;
			float rightDistance = rightHit ? rightHit->Distance : INFINITY;
			float forwardDistance = forwardHit ? forwardHit->Distance : INFINITY;
			float backDistance = backHit ? backHit->Distance : INFINITY;

			// Compare and correct the movemnt for the closest distances.
			m_MovementInput.y = rightDistance < leftDistance ? 1.0f : -1.0f;
			m_MovementInput.x = backDistance < forwardDistance ? 1.0f : -1.0f;
			m_MovementInput = glm::normalize(m_MovementInput);

			m_TooCloseToWall = true;
		}
		else
		{
			// Randomize movement again when wall distance is fixed.
			if (m_TooCloseToWall)
			{
				RandomizeMovementInput();
			}

			m_TooCloseToWall = false;
		}
	}

	bool TankInputAshEnemy::IsAimingAtEnemy()
	{
		// Get raycast data.
		glm::vec3 origin = m_GunTransform->GetPosition() + m_GunTransform->GetForward() * 2.0f;
		glm::vec3 direction = m_GunTransform->GetForward();

		// Shoot ray.
		RefPtr<Physics::RaycastHit> hit = Physics::Physics::RayCast(origin, direction, 1000);

		// Flag bool if aiming at enemy.
		return hit && hit->HitObject->GetName() == "EnemyTank";
	}
}