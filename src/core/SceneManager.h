// 2022 Tygo Boons

#pragma once
#include "Scene.h"

namespace Core
{
	class SceneManager
	{
	public:
		// Get current active scene.
		Scene* GetActiveScene() { return s_ActiveScene; }

		// Set/Replace active scene.
		void SetActiveScene(Scene* scene);

	private:
		Scene* s_ActiveScene;
	};
}