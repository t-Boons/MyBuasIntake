// 2022 Tygo Boons

#pragma once

#include "mypch.h"
#include "Core/Core.h"
#include "GameObject.h"

// Macro to simplify print messages

#define GAMEOBJECT_IDENTITY "OBJ: " + Parent->GetName() + " ID: " + STR(Parent->GetID()) + " "



// Macro to make component name implementation easier.

#define IMPLEMENT_COMPONENT_IDENTIFIER(name) 				public:\
																virtual std::string GetTypeName() const override { return #name; } \
																static std::string GetStaticName() { return #name; }\
																static RefPtr<name> Create() { return std::make_shared<name>(); }\
																virtual name* Copy() override {return new name(*this);}

#define IMPLEMENT_COMPONENT_IDENTIFIER_INHERIT(name, base)  public:\
																virtual std::string GetTypeName() const override { return #base; } \
																static std::string GetStaticName() { return #base; }\
																static RefPtr<name> Create() { return std::make_shared<name>(); }\
																virtual name* Copy() override {return new name(*this);}


namespace Entity
{
	class Component : public std::enable_shared_from_this<Component>
	{
	public:

		// Return a copy of this component.
		virtual Component* Copy() = 0;

		// Return componnt type name.
		virtual std::string GetTypeName() const = 0;
		
		// Start is called before the first update.
		virtual void Start() {};

		// Update is called once per frame.
		virtual void Update() {};

		// Get component of this gameobject.
		template<class T>
		RefPtr<T> GetComponent()
		{
			return Parent->GetComponent<T>();
		}

		// Get multiple component of this gameobject.
		template<class T>
		std::vector<RefPtr<T>> GetComponents()
		{
			return Parent->GetComponents<T>();
		}

		// Add Component to this gameobject.
		template<class T>
		RefPtr<T> AddComponent(RefPtr<T>& component)
		{
			return Parent->AddComponent<T>(component);
		}

		// Destroy this component.
		void Destroy()
		{
			// Remove this component from the gameobject.
			Parent->RemoveComponent(shared_from_this());
		}

		// Virtual destructor for memory cleanup.
		virtual ~Component() = default;

	public:
		GameObject* Parent = nullptr;
	};
}