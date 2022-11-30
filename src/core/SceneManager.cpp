#include "SceneManager.h"

namespace Core
{
	void SceneManager::SetActiveScene(Scene* scene)
	{
		// Unload scene if assigned.
		if (s_ActiveScene)
		{
			s_ActiveScene->UnloadScene();
		}

		s_ActiveScene = scene;

		s_ActiveScene->LoadScene();
	}
}