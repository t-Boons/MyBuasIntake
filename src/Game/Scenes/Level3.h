// 2022 Tygo Boons

#pragma once

#include "Scene/Scene.h"
#include "Core/core.h"

namespace Gameplay
{
	class Level3 : public Core::Scene
	{
		MAKE_SHARED(Level3)
		SCENE_NAME(Level3)
	public:
		// Inherited via Scene.
		virtual void LoadScene() override;
	};
}