// 2022 Tygo Boons

#include "mypch.h"
#include "TankEngine.h"
#include "Utils/TimedEvent.h"

namespace Gameplay
{
	void TankEngine::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();
		m_TankInput = GetComponent<TankInput>();
		m_ExplosionSound = GetComponent<Entity::AudioSource>();

		m_ReduceSpeedTimer = 0;
		m_IsDead = false;
	}

	void TankEngine::Update()
	{
		float dt = Core::Time::GetDeltaTime();

		glm::vec2 input = m_TankInput->GetMovementInput();

		float speed = 1;

		// Check if player is shooting
		if (m_TankGun->IsShooting())
		{
			m_ReduceSpeedTimer = 0;
		}

		// Add a speed reduction if the player recently shot.
		if (m_ReduceSpeedTimer < SPEED_REDUCTION_TIME)
		{
			speed -= sinf(m_ReduceSpeedTimer * glm::pi<float>());
			m_ReduceSpeedTimer += dt;
		}

		// Update movement.
		m_Transform->Translate(input.x * m_Transform->GetForward() * dt * speed * MOVEMENT_SPEED);
		m_Transform->Rotate(input.y * glm::vec3(0, 1, 0) * dt * speed * -ROTATION_SPEED);
	}

	void TankEngine::OnCollisionEnter(RefPtr<Physics::Collision> collision)
	{
		// Ignore if the tank is dead. (required because this instance is deleted after a small delay)
		if (m_IsDead)
		{
			return;
		}

		if (collision->HitObject->GetName() == "Bullet")
		{
			m_IsDead = true;

			m_ExplosionSound->Play();
			
			// Remove collider.
			Parent->GetComponent<Entity::BoxCollider>()->Destroy();

			// Remove all renderers from tank body.
			std::vector<RefPtr<Entity::MeshRenderer>> renderers = Parent->GetComponents<Entity::MeshRenderer>();
			for (size_t i = 0; i < renderers.size(); i++)
			{
				renderers[i]->Destroy();
			}

			// Remove player gun renderer.
			m_TankGun->Parent->Destroy();

			LOG_WARN(GAMEOBJECT_IDENTITY + "Has died.")

			Utils::TimedEvent(DELETION_DELAY, [=]()
				{
					// Call OnDie function on tank manager. Changes depending on if its an enemy or player tank.
					if (Parent->GetName() == "PlayerTank")
					{
						Entity::GameObject::FindObjectOfType<TankManager>()->OnPlayerDie();
					}
					else
					{
						Entity::GameObject::FindObjectOfType<TankManager>()->OnEnemyDie();
					}

					// Destroy this gameobject.
					Parent->Destroy();
				});



		}
	}
}