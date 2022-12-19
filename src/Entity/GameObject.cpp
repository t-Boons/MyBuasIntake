// 2022 Tygo Boons

#include "mypch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core/Game.h"
#include "Entity/ScriptComponent.h" 

namespace Entity
{
	GameObject::GameObject(const std::string& name)
		: m_Name(name)
	{
		// Add default Transform Component.
		AddComponent(Transform::Create());
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
			LOG_WARN("GameObject: " + GetName() + " " + "Has been destroyed.")

			// Remove this object from the scene.
			Core::Game::Get()->GetSceneManager()->GetActiveScene()->RemoveFromScene(this);

			// Delete components.
			m_Components.clear();
		}

		return m_QueueForDeletion;
	}

	const RefPtr<GameObject>& GameObject::Find(const std::string& name)
	{
		return Core::Game::Get()->GetSceneManager()->GetActiveScene()->FindEntityByName(name);
	}

	RefPtr<Entity::GameObject> GameObject::Instantiate(const RefPtr<Entity::GameObject>& object, const glm::vec3& position, const glm::quat& rotation)
	{
		// Set position and rotation.
		RefPtr<Entity::Transform> transform = object->GetComponent<Entity::Transform>();
		transform->SetPosition(position);
		transform->SetRotation(rotation);

		Core::Game::Get()->GetSceneManager()->GetActiveScene()->AddToScene(object);

		object->StartComponents();

		return object;
	}

	RefPtr<Entity::GameObject> GameObject::Instantiate(const RefPtr<Entity::GameObject>& object)
	{
		return Instantiate(object, glm::vec3(0.0f), glm::quat(glm::vec3(0.0f)));
	}
}