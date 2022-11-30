// 2022 Tygo Boons
#include "TankMovement.h"

using namespace Entity;

namespace Gameplay
{

	void TankMovement::Start()
	{
		m_Transform = GetComponent<Transform>();
	}

	void TankMovement::Update()
	{
		Parent->GetComponent<Entity::Transform>();
	}
}