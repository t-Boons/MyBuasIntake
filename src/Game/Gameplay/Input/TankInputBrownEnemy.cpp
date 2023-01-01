// Tygo Boons 2022

#include "mypch.h"

#include "TankInputBrownEnemy.h"

namespace Gameplay
{
	void TankInputBrownEnemy::UpdateInput()
	{
		// Make sure enemy tank only shoots once.
		m_Shoot = false;


		glm::vec3 playerPos = Entity::GameObject::Find("PlayerTank")->GetComponent<Entity::Transform>()->GetPosition();
		glm::vec3 myPos = GetComponent<Entity::Transform>()->GetPosition();
		glm::vec2 lookPos = glm::vec2(playerPos.z, playerPos.x) - glm::vec2(myPos.z, myPos.x);

		m_GunInput = lookPos;


		m_Timer += Core::Time::GetDeltaTime();

		if (m_Timer > m_RandomValue)
		{
			// Reset Timer
			m_Timer = 0;

			// Generate new random value.
			m_RandomValue = rand() % 1000 / 1000.0f * MAX_STATE_TIME;

			RandomizeInputs();
		}
	}

	void TankInputBrownEnemy::RandomizeInputs()
	{
		m_MovementInput.x = (rand() % 1000) / 1000.0f;
		m_MovementInput.y = (rand() % 1000) / 1000.0f;

		m_Shoot = rand() % 2 == 1;
	}
}