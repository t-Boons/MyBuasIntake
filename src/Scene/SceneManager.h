// 2022 Tygo Boons

#pragma once
#include "Scene.h"
#include "Core/Core.h"

namespace Core
{
	class SceneManager
	{
		MAKE_SHARED(SceneManager)

	public:
		// Update scene loading state.
		void Update();

		// Get current active scene.
		const RefPtr<Scene>& GetActiveScene() { return m_ActiveScene; }

		// Set/Replace active scene.
		void SetActiveScene(const RefPtr<Scene>& scene);

	private:
		RefPtr<Scene> m_ActiveScene;
		RefPtr<Scene> m_QueuedScene;
		bool m_HasQueuedScene;
	};
}