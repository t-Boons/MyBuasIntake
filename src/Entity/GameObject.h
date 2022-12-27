// 2022 Tygo Boons

#pragma once

#include "Core/Core.h"
#include <iostream>
#include "Physics/AABB.h"

namespace Entity
{
	class Component;

	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		// Construct game object.
		GameObject(const std::string& name);

		// Copy gameobject constructor.
		GameObject(const GameObject& object);

		// Destroy game object.
		~GameObject();

		MAKE_SHARED_ONEPARAM(GameObject, const std::string&, name)

		template<class T>
		const RefPtr<T> GetComponent()
		{
			// Search for component of type in components.
			for (auto& component : m_Components)
			{
				// Return if static type and local type match.
				if (component->GetTypeName() == T::GetStaticName())
				{
					return std::dynamic_pointer_cast<T>(component);
				}
			}

			return nullptr;
		}

		template<class T>
		const std::vector<RefPtr<T>> GetComponents()
		{
			std::vector<RefPtr<T>> components;

			// Search for components of type in components.
			for (auto& component : m_Components)
			{
				// Add item if type matches.
				if (component->GetTypeName() == T::GetStaticName())
				{
					components.push_back(std::dynamic_pointer_cast<T>(component));
				}
			}

			return components;
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

		// Removes a component from the gameobject.
		void RemoveComponent(const RefPtr<Component>& toRemove);

		// Call start on all components.
		void StartComponents();

		// Update all components.
		void UpdateComponents();

		// Update collision events.
		void UpdateCollisionEvents(RefPtr<Physics::Collision> collision);

		// Get entity name.
		const std::string& GetName() const { return m_Name; }

		// Get the entitys instance ID
		uint64_t GetID() const { return m_ID; }

		// Destroy this entity.
		void Destroy();

		// Find object with name.
		static RefPtr<GameObject> Find(const std::string& name);

		// Find component in scene.
		template<typename T>
		static RefPtr<T> FindObjectOfType()
		{
			return Core::Game::Get()->GetSceneManager()->GetActiveScene()->FindObjectOfType<T>();
		}

		// Spawn game object with rotation and position.
		static RefPtr<GameObject> Instantiate(const RefPtr<GameObject>& object, const glm::vec3& position, const glm::quat& rotation);

		// Spawn game object.
		static RefPtr<GameObject> Instantiate(const RefPtr<GameObject>& object);

		// Create copy of this instance
		RefPtr<GameObject> Copy();

	private:
		std::vector<RefPtr<Component>> m_Components;
		std::string m_Name;
		uint64_t m_ID;

		static uint64_t s_GameObjectCount;
	};
}