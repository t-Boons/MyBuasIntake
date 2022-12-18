// 2022 Tygo Boons

#pragma once

#include "Scene/Scene.h"

namespace Gameplay
{
	class Level1 : public Core::Scene
	{
	public:
		// Inherited via Scene.
		virtual void LoadScene() override;


	private:
		void CreateEnviroment();
		void CreatePlayerTank();
		void CreateSceneCamera();
	};
}