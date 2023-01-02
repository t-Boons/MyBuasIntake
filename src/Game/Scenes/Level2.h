// 2022 Tygo Boons

#pragma once

#include "Scene/Scene.h"
#include "Core/core.h"

#define USE_SPECTATOR_CAMERA false

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