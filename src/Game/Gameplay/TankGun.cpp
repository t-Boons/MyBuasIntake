// 2022 Tygo Boons

#include "mypch.h"
#include "TankGun.h"

namespace Gameplay
{
	void TankGun::Start()
	{
		// Get transform component from tank body.
		m_ParentTransform = Entity::GameObject::Find("TankPlayer")->GetComponent<Entity::Transform>();

		// Get this transform.
		m_Transform = GetComponent<Entity::Transform>();
	}

	void TankGun::Update()
	{
		// Set position equal to tank body position.
		m_Transform->SetPosition(m_ParentTransform->GetPosition());


		// Rotate turret.
		m_Transform->Rotate({ 0, 50 * Core::Time::GetDeltaTime(), 0 });
	}
}