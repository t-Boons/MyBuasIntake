// 2022 Tygo Boons

#pragma once
#include "Scene.h"

namespace Core
{
	class TestScene : public Scene
	{
		// Inherited via Scene.
		virtual void LoadScene() override;
	};
}