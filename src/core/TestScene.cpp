// 2022 Tygo Boons

#include "TestScene.h"
#include "Entity/GameObject.h"

namespace Core
{
	void TestScene::LoadScene()
	{
		// Load TestScene by adding entities.
		RefPtr<Entity::GameObject> go = std::make_shared<Entity::GameObject>("Hi");
		m_Entities.push_back(go);
	}

}