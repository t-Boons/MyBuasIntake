// 2022 Tygo Boons

#pragma once

#include "Core/Core.h"
#include <iostream>
#include "Physics/AABB.h"

namespace Entity
{
	class Component;

	class GameObject
	{
	public:
		GameObject(const std::string& name);

		MAKE_SHARED_ONEPARAM(GameObject, const std::string&, name)

		template<class T>
		const RefPtr<T> GetComponent()
		{
			// Search for component of type in components.
			for (auto& component : m_Components)
			{
				// Return if static type and local type match.
				if (component->GetTypeName() == T::GetStaticName())
					return std::dynamic_pointer_cast<T>(component);
			}

			return nullptr;
		}

		// Add component to entity.
		template<class T>
		inline RefPtr<T> AddComponent(RefPtr<T>& component)
		{
			// Add component to list
			m_Components.push_back(component);

			// Set component parent reference to this.	
			static_cast<GameObject*>(component.get()->Parent) = this;

			return component;
		}


		// Call start on all components.
		void StartComponents();

		// Update all components.
		void UpdateComponents();

		// Update collision events.
		void UpdateCollisionEvents(RefPtr<Physics::Collision> collision);

		// Get entity name.
		const std::string& GetName() const { return m_Name; }

		// Destroy this entity.
		void Destroy();

		// Check if object is queued for deletion.
		bool QueuedForDeletion();

		// Find object with name.
		static RefPtr<GameObject> Find(const std::string& name);

		// Spawn game object with rotation and position.
		static RefPtr<Entity::GameObject> Instantiate(const RefPtr<Entity::GameObject>& object, const glm::vec3& position, const glm::quat& rotation);

		// Spawn game object.
		static RefPtr<Entity::GameObject> Instantiate(const RefPtr<Entity::GameObject>& object);

	private:
		std::vector<RefPtr<Component>> m_Components;
		std::string m_Name;
		bool m_QueueForDeletion = false;
	};
}