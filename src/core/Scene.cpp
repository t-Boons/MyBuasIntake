// 2022 Tygo Boons

#include "Scene.h"

void Core::Scene::UnloadScene()
{
	// Destroy this instance.
	delete(this);
}

void Core::Scene::Update()
{
	// Update all entity Components.
	for (auto& obj : m_Entities)
	{
		obj->UpdateComponents();
	}

}
