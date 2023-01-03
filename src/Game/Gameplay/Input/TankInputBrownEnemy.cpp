// 2022 Tygo Boons

#include "mypch.h"

#include "TankInputBrownEnemy.h"
#include "Game/Gameplay/TankEngine.h"

namespace Gameplay
{
	void TankInputBrownEnemy::StartInput()
	{
		StartShootInput();
		StartGunDirectionInput();

		/// Set the current rotation to the gun forward vector
		// Get tank gun forward vector.
		glm::vec3 gunForward = GetComponent<TankEngine>()->GetGunObject()->GetComponent<Entity::Transform>()->GetForward();
		gunForward.y = 0;
		gunForward = glm::normalize(gunForward);

		// Set the current rotation to the forwrad rotation of the gun.
		m_CurrentRotation = std::atan2(gunForward.x, gunForward.z) - glm::pi<float>() * 0.5f;
	}

	void TankInputBrownEnemy::UpdateInput()
	{
		// Update rotation.
		m_CurrentRotation += m_RotationMultiplier * Core::Time::GetDeltaTime();

		// Make the run rotate around
		m_GunInput = glm::vec2(glm::sin(glm::pi<float>() * m_CurrentRotation),
							   glm::cos(glm::pi<float>() * m_CurrentRotation));

	}

	void TankInputBrownEnemy::StartShootInput()
	{
		// Create timed event to shoot the gun;
		Utils::TimedEvent e(Utils::Random::Range(MIN_WAIT_SHOOT_TIME, MAX_WAIT_SHOOT_TIME), [=]()
			{
				Shoot();
				StartShootInput();
			});
	}

	void TankInputBrownEnemy::StartGunDirectionInput()
	{
		// Set random rotation multiplier.
		m_RotationMultiplier = Utils::Random::Range(-GUN_ROTATION_SPEED_MAX_MULTIPLIER * 0.5f, GUN_ROTATION_SPEED_MAX_MULTIPLIER * 0.5f);

		Utils::TimedEvent e(Utils::Random::Range(0.0f, RANDOM_GUN_DIRECTION_CHANGE_TIME), [=]()
			{
				StartGunDirectionInput();
			});
	}
}