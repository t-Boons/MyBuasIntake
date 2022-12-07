// 2022 Tygo Boons

#pragma once
#include "Entity/BoxCollider.h"
#include "Entity/PhysicsBody.h"

namespace Physics
{
	class PhysicsEnviroment
	{
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

	private:
		bool AnyIntersections(const RefPtr<Entity::BoxCollider>& collider);

	private:

		std::vector<RefPtr<Entity::BoxCollider>> m_ColliderComponents;
		std::vector<RefPtr<Entity::PhysicsBody>> m_PhysicsBodyComponents;
	};
}
