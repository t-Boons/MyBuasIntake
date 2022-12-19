// 2022 Tygo Boons

#pragma once

#include "Scene/Scene.h"

#define USE_SPECTATOR_CAMERA 1

namespace Gameplay
{
	class Level1 : public Core::Scene
	{
	public:
		// Inherited via Scene.
		virtual void LoadScene() override;
	};
}