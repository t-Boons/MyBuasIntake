// 2022 Tygo Boons

#pragma once
#include "Entity/BoxCollider.h"
#include "Entity/PhysicsBody.h"
#include "Core/Core.h"

namespace Physics
{

	class PhysicsEnviroment
	{
		MAKE_SHARED(PhysicsEnviroment)

	public:
		// Add collider to physics enviroment.
		void RegisterComponent(const RefPtr<Entity::BoxCollider> collider);

		// Add physicsbody to physics enviroment.
		void RegisterComponent(const RefPtr<Entity::PhysicsBody> pBody);

		// Remove collider from physics enviroment.
		void RemoveComponent(const RefPtr<Entity::BoxCollider> collider);

		// Remove physicsbody from physics enviroment.
		void RemoveComponent(const RefPtr<Entity::PhysicsBody> pBody);

		// Update all physics.
		void Update();

		// Get all collider components.
		const std::vector<RefPtr<Entity::BoxCollider>>& GetColliderComponents() const { return m_ColliderComponents; }

	private:
		// Sees if there are any collisions found.
		RefPtr<Collision> AnyIntersections(const RefPtr<Entity::BoxCollider>& collider);

		// Pushes the collision events to the scene.
		void PushEvent(const RefPtr<Collision>& collision);

	private:

		std::vector<RefPtr<Entity::BoxCollider>> m_ColliderComponents;
		std::vector<RefPtr<Entity::PhysicsBody>> m_PhysicsBodyComponents;
	};
}
