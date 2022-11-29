// 2022 Tygo Boons

#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Transform.h"
#include <SFML/Graphics.hpp>


namespace Entity
{
	class GameObject
	{
	public:
		GameObject(const std::string& name = "")
			: m_Name(name)
		{
			// Set default name if object does not have a name.
			if (m_Name == "")
				m_Name = "New Game Object " + std::to_string(m_ObjectID);

			// Add default Transform Component.
			RefPtr<Transform> a(new Transform);
			AddComponent(a);
		}

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
		inline RefPtr<T> AddComponent(const RefPtr<T>& component)
		{
			// Add component to list
			m_Components.push_back(component);

			return component;
		}

		// Update all components.
		void UpdateComponents();

		// Get transform component reference.
		const RefPtr<Transform> GetTransform() const { return std::dynamic_pointer_cast<Transform>(m_Components[0]); }

		// Get entity name.
		const std::string& GetName() const { return m_Name; }

		// Destroy this entity.
		void Destroy();

	private:
		std::vector<RefPtr<Component>> m_Components;
		std::string m_Name;
		uint32_t m_ObjectID;
	};
}