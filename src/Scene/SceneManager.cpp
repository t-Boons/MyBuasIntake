// 2022 Tygo Boons

#include "mypch.h"
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

		// Set active scene to current scene.
		s_ActiveScene = scene;

		// Load the scene.
		s_ActiveScene->LoadScene();

		// Call start on all the behaviour.
		s_ActiveScene->Start();
	}
}