// 2023 Tygo Boons

#pragma once

#include "Scene/Scene.h"
#include "Core/core.h"

namespace Gameplay
{
	class Level4 : public Core::Scene
	{
		MAKE_SHARED(Level4)
		SCENE_NAME(Level4)

	public:
		// Inherited via Scene.
		virtual void LoadScene() override;
	};
}