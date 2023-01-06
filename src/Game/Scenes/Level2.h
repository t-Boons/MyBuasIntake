// 2023 Tygo Boons

#pragma once

#include "Scene/Scene.h"
#include "Core/core.h"

namespace Gameplay
{
	class Level2 : public Core::Scene
	{
		MAKE_SHARED(Level2)
		SCENE_NAME(Level2)

	public:
		// Inherited via Scene.
		virtual void LoadScene() override;
	};
}