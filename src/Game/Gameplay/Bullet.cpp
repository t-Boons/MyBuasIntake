// 2022 Tygo Boons

#include "mypch.h"
#include "Bullet.h"
#include "Core/Game.h"
#include "Core/Time.h"
#include "Core/Core.h"

namespace Gameplay
{

	void Bullet::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();
		m_Hits = 0;
	}

	void Bullet::Update()
	{
		float dt = Core::Time::GetDeltaTime();

		// Move forward.
		m_Transform->Translate(m_Transform->GetForward() * dt * 10.0f);
	}

	void Bullet::OnCollisionEnter(RefPtr<Physics::Collision> collision)
	{
		LOG(VEC3STR(collision->Normal))
		m_Transform->SetRotation(glm::quatLookAt(glm::reflect(m_Transform->GetForward(), collision->Normal), glm::vec3(0.0f, 1.0f, 0.0f)));

		m_Hits++;

		if (m_Hits >= 2)
		{
			Parent->Destroy();
		}
	}
}