// 2022 Tygo Boons

#pragma once

#include "Core/Core.h"
#include "Entity/Components.h"
#include "Core/Time.h"
#include "Game/Gameplay/TankInput.h"

namespace Gameplay
{
	class TankGun : public Entity::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(TankGun)

	public:
		virtual void Start() override;

		virtual void Update() override;

		void SetGunRotation(const glm::vec2& direction);

	private:
		RefPtr<Entity::Transform> m_ParentTransform;
		RefPtr<Entity::Transform> m_Transform;
		RefPtr<TankInput> m_Input;
	};
}