// 2022 Tygo Boons

#pragma once

#include "Component.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"

namespace Entity
{
	class BoxCollider : public Component
	{
		IMPLEMENT_COMPONENT_IDENTIFIER(BoxCollider)

	public:

		virtual void Update() override;
	};
}