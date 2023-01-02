// 2023 Tygo Boons

#pragma once

#include "glm/glm.hpp"
#include "PhysicsEnviroment.h"
#include "Core/core.h"
#include "Entity/GameObject.h"

// Forward declaration for gameobject.
namespace Entity
{
	class GameObject;
}

namespace Physics
{
	struct RaycastHit
	{
		MAKE_SHARED(RaycastHit)

		glm::vec3 Point;
		float Distance;
		Entity::GameObject* HitObject;
	};

	class Physics
	{
	public:

		// Get all intersecting objects from raycast.
		static std::vector<RefPtr<RaycastHit>> RayCastAll(const glm::vec3& origin, const glm::vec3& direction, float distance);

		// Shoot a ray and return the most nearby object
		static RefPtr<RaycastHit> RayCast(const glm::vec3& origin, const glm::vec3& direction, float distance);

		// Return physics enviroment reference.
		static RefPtr<PhysicsEnviroment> GetPhysicsEnviroment() { return s_Enviroment; }

		// Set physics enviroment reference.
		static void SetPhysicsEnviroment(RefPtr<PhysicsEnviroment> enviroment) { s_Enviroment = enviroment; }

	private:
		static RefPtr<PhysicsEnviroment> s_Enviroment;
	};
}