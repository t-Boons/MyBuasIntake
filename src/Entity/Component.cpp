// 2023 Tygo boons

#include "mypch.h"
#include "Component.h"
#include "Utils/TimedEvent.h"

Entity::Component::~Component()
{
	// Delete all timed events from this component if there are any.
	Utils::TimedEventContainer::DeleteCaller(this);
}
