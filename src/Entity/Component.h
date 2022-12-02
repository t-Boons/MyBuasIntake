// 2022 Tygo Boons

#pragma once

#include "mypch.h"
#include "Core/Core.h"
#include "GameObject.h"

// Macro to make component name implementation easier.

#define IMPLEMENT_COMPONENT_IDENTIFIER(name) 	public:\
													virtual std::string GetTypeName() const override { return #name; } \
													static std::string GetStaticName() { return #name; }\
													static RefPtr<name> Create() { return std::make_shared<name>(); }


namespace Entity
{
	class Component
	{
	public:

		// Return componnt type name.
		virtual std::string GetTypeName() const = 0;
		
		// Start is called before the first update.
		virtual void Start() {};

		// Update is called once per frame.
		virtual void Update() {};

		// Virtual destructor for memory cleanup.
		virtual ~Component() = default;

	public:
		GameObject* Parent = nullptr;
	};
}