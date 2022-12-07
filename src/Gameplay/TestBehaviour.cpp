// 2022 Tygo Boons

#include "mypch.h"

#include "TestBehaviour.h"
#include "Core/Time.h"

namespace Gameplay
{
	void TestBehaviour::Start()
	{
		m_Transform = GetComponent<Entity::Transform>();
	}

	void TestBehaviour::Update()
	{
		glm::vec3 pos = { 0, 0, 0 };

		pos.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) * 5 + sf::Keyboard::isKeyPressed(sf::Keyboard::Down) * -5;
		pos.x = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) * 5 + sf::Keyboard::isKeyPressed(sf::Keyboard::Right) * -5;

		m_Transform->Translate(pos * Core::Time::GetDeltaTime());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			Parent->Destroy();
	}

	void TestBehaviour::OnCollisionEnter()
	{
		LOG_ERROR("Collided")
	}
}