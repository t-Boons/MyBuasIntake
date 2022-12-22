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

		LOG_NOTIF("CREATED: " + GetName() + " ID: " + STR(m_ID))
	}

	GameObject::GameObject(const GameObject& object)
	{
		// Set gameobject ID.
		m_ID = s_GameObjectCount;

		// Increment gameobject counter.
		s_GameObjectCount++;

		// Resize component array to object.component size;
		m_Components.resize(object.m_Components.size());

		// Copy all component data.
		for (size_t i = 0; i < m_Components.size(); i++)
		{
			// Copy the existing component.
			Entity::Component* componentCopy = object.m_Components[i]->Copy();

			// Set component parent to new gmaeobject.
			componentCopy->Parent = this;

			// Assign ptr to new component array.
			m_Components[i] = static_cast<RefPtr<Entity::Component>>(componentCopy);
		}

		m_Name = std::string(object.m_Name);

		LOG_NOTIF("COPIED:  " + GetName() + " ID: " + STR(m_ID))
	}

	GameObject::~GameObject()
	{
		// Decrement gameobject counter.
		s_GameObjectCount--;

		LOG_NOTIF("DELETED: " + GetName() + " ID: " + STR(m_ID))
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

	RefPtr<GameObject> GameObject::Find(const std::string& name)
	{
		return Core::Game::Get()->GetSceneManager()->GetActiveScene()->FindEntityByName(name);
	}

	RefPtr<Entity::GameObject> GameObject::Instantiate(const RefPtr<Entity::GameObject>& object, const glm::vec3& position, const glm::quat& rotation)
	{
		// Copy gameobject.
		RefPtr<Entity::GameObject> newObject = object->Copy();

		// Set position and rotation.
		RefPtr<Entity::Transform> transform = newObject->GetComponent<Entity::Transform>();
		transform->SetPosition(position);
		transform->SetRotation(rotation);

		// Add the object to the scene.
		Core::Game::Get()->GetSceneManager()->GetActiveScene()->AddEntityToInstantiationQueue(newObject);

		return newObject;
	}

	RefPtr<Entity::GameObject> GameObject::Instantiate(const RefPtr<Entity::GameObject>& object)
	{
		return Instantiate(object, glm::vec3(0.0f), glm::quat(glm::vec3(0.0f)));
	}

	void GameObject::Destroy()
	{
		Core::Game::Get()->GetSceneManager()->GetActiveScene()->AddEntityToDeletionQueue(shared_from_this());
	}

	RefPtr<GameObject> GameObject::Copy()
	{
		return	std::make_shared<Entity::GameObject>(*this);
	}
}