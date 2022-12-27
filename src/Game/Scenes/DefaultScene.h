// 2022 Tygo Boons

#pragma once

#include "Scene/Scene.h"
#include "Core/core.h"

namespace Gameplay
{
	class DefaultScene : public Core::Scene
	{
		MAKE_SHARED(DefaultScene)

	public:
		// Inherited via Scene.
		virtual void LoadScene() override;
	};
}