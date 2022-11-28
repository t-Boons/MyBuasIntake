// 2022 Tygo Boons

#pragma once
#include <string>

// Macro to make component name implementation easier.
#define IMPLEMENT_COMPONENT_IDENTIFIER(name) 		public:\
													virtual std::string GetTypeName() const override { return #name; } \
													static std::string GetStaticName() { return #name; }

namespace Entity
{
	class Component
	{
	public:

		// Return componnt type name.
		virtual std::string GetTypeName() const = 0;

		// Update component.
		virtual void Update() {};

		// Make GameObject a friend class so it can acces the SetParent function.
		friend class GameObject;

	private:

		// Set the component parent object.
		void SetParent(GameObject* object)  { m_This = object; }
		
	protected:
		GameObject* m_This;
	};
}