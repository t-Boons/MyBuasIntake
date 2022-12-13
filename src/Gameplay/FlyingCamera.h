// 2022 Tygo Boons

#pragma once

#include "Gameplay/ScriptComponent.h"
#include "Entity/Camera.h"
#include "Entity/Transform.h"
#include "glm/glm.hpp"

namespace Gameplay
{
	class FlyingCamera : public Gameplay::ScriptComponent
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(FlyingCamera)

	public:
		virtual void Start() override;

		virtual void Update() override;

	private:

		// Get delta vector based on keyboard input.
		glm::vec3 GetPositionDeltaFromInput();

		// Get delta vector based on mouse input.
		glm::vec3 GetRotationDeltaFromInput();

	private:
		RefPtr<Entity::Camera> m_Camera;
		glm::vec2 m_MouseDelta = { 0, 0 };
		RefPtr<Entity::Camera> m_ActiveCamera;
	};
}