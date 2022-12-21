// 2022 Tygo Boons

#include "mypch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core/Game.h"
#include "Entity/ScriptComponent.h" 

namespace Entity
{
	uint64_t GameObject::s_GameObjectCount = 0;

	GameObject::GameObject(const std::string& name)
		: m_Name(name)
	{
		// Add default Transform Component.
		AddComponent(Transform::Create());

		// Set gameobject ID.
		m_ID = s_GameObjectCount;

		// Increment gameobject counter.
		s_GameObjectCount++;

		LOG_INFO("Created: GameObject " + GetName() + " " + "ID: " + STR(m_ID))
	}

	GameObject::GameObject(const GameObject& object)
	{
		// Set gameobject ID.
		m_ID = s_GameObjectCount;

		// Increment gameobject counter.
		s_GameObjectCount++;

		// Copy data.
		m_Components.resize(object.m_Components.size());

		// TODO Make component have new data.
		m_Name = std::string(object.m_Name);

		LOG_WARN("Copied:  GameObject " + object.GetName() + " ID: " + STR(m_ID))
	}

	GameObject::~GameObject()
	{
		// Decrement gameobject counter.
		s_GameObjectCount--;
	}

	void GameObject::StartComponents()
	{
		// Loop through all components
		for (auto& c : m_Components)
		{
			c->Start();
		}
	}

	void GameObject::UpdateComponents()
	{
		// Return if object has to be deleted.
		if (QueuedForDeletion())
		{
			return;
		}

		// Loop through all components
		for (size_t i = 0; i < m_Components.size(); i++)
		{
			m_Components[i]->Update();
		}
	}

	void GameObject::UpdateCollisionEvents(RefPtr<Physics::Collision> collision)
	{
		// Run collision event for every scriptcomponent
		for (auto& c : m_Components)
		{
			Entity::ScriptComponent* scriptComponent = dynamic_cast<Entity::ScriptComponent*>(c.get());

			// Run collision if cast is succesful.
			if (scriptComponent)
			{
				scriptComponent->OnCollisionEnter(collision);
			}
		}
	}

	void GameObject::Destroy()
	{
		ASSERT(this != nullptr, "The object you're trying to destroy is nullptr.")

		m_QueueForDeletion = true;
	}

	bool GameObject::QueuedForDeletion()
	{
		if (m_QueueForDeletion)
		{
			LOG_WARN("Deleted: GameObject " + GetName() + " ID:" + STR(m_ID))

			// Remove this object from the scene.
			Core::Game::Get()->GetSceneManager()->GetActiveScene()->RemoveFromScene(this);

			// Delete components.
			m_Components.clear();
		}

		return m_QueueForDeletion;
	}

	RefPtr<GameObject> GameObject::Find(const std::string& name)
	{
		return Core::Game::Get()->GetSceneManager()->GetActiveScene()->FindEntityByName(name);
	}

	RefPtr<Entity::GameObject> GameObject::Instantiate(const RefPtr<Entity::GameObject>& object, const glm::vec3& position, const glm::quat& rotation)
	{
		// Copy gameobject.
		RefPtr<Entity::GameObject> newObject = std::make_shared<Entity::GameObject>(*object);

		// Set position and rotation.
		RefPtr<Entity::Transform> transform = newObject->GetComponent<Entity::Transform>();
		transform->SetPosition(position);
		transform->SetRotation(rotation);

		// Add the object to the scene.
		Core::Game::Get()->GetSceneManager()->GetActiveScene()->AddToScene(object);

		// Call start on component.
		newObject->StartComponents();

		return newObject;
	}

	RefPtr<Entity::GameObject> GameObject::Instantiate(const RefPtr<Entity::GameObject>& object)
	{
		return Instantiate(object, glm::vec3(0.0f), glm::quat(glm::vec3(0.0f)));
	}
}