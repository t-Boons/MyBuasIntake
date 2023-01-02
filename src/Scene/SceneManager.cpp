// 2022 Tygo Boons

#include "mypch.h"
#include "SceneManager.h"
#include "Utils/TimedEvent.h"

namespace Core
{
	void SceneManager::Update()
	{
		if (m_HasQueuedScene)
		{
			m_HasQueuedScene = false;

			// Unload current scene.
			if (m_ActiveScene)
			{
				LOG_NOTIF("UNLOADING SCENE: " + m_ActiveScene->GetSceneName())
				m_ActiveScene->UnloadScene();
			}

			// Clear all timed events to avoid nullref errors.
			Utils::TimedEventContainer::Reset();

			// Set active scene to current scene.
			m_ActiveScene = m_QueuedScene;

			// Load the scene.
			LOG_NOTIF("LOADING SCENE: " + m_ActiveScene->GetSceneName())
			m_ActiveScene->LoadScene();

			// Call start on all the behaviour.
			m_ActiveScene->Start();
		}
	}

	void SceneManager::SetActiveScene(const RefPtr<Scene>& scene)
	{
		m_QueuedScene = scene;
		m_HasQueuedScene = true;
	}
}