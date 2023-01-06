// Tygo Boons 2022

#pragma once

#include "Entity/Component.h"

namespace Utils
{
	// Timed event is used to add events to the event container so they don't rely on lifetime.
	struct TimedEvent
	{
		//template<typename Function>
		TimedEvent(float time, void* caller, std::function<void()> eventFunc);
	};

	// Timed container contains all the events.
	class TimedEventContainer
	{
	public:

		// Update event times.
		static void Update(float deltaTime);

		// Add event to container.
		static void AddEvent(float timeUntillExecute, void* caller, std::function<void()> eventFunc);

		// Destroys all events.
		static void Reset();

		// Delete a caller.
		static void DeleteCaller(void* caller);

	private:
		static std::vector<std::pair<std::function<void()>, float>> s_ActiveEvents;
		static std::vector<float> s_ActiveEventTimes;
		static std::vector<void*> s_ActiveEventCallers;
	};
}