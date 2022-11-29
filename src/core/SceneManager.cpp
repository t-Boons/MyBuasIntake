#include "SceneManager.h"

namespace Core
{
	void SceneManager::SetActiveScene(Scene* scene)
	{
		s_ActiveScene->UnloadScene();

		s_ActiveScene = scene;

		s_ActiveScene->LoadScene();
	}
}