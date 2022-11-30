// 2022 Tygo Boons

#pragma once
#include "Core/Core.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Entity
{
	class Component;

	class GameObject
	{
	public:
		GameObject(const std::string& name = "");

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

		// Get entity name.
		const std::string& GetName() const { return m_Name; }

		// Destroy this entity.
		void Destroy();

	private:
		std::vector<RefPtr<Component>> m_Components;
		std::string m_Name;
	};
}