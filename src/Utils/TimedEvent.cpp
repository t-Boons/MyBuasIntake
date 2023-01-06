// Tygo Boons 2022

#include "mypch.h"
#include "TimedEvent.h"
#include "Core/core.h"

namespace Utils
{
	std::vector<std::pair<std::function<void()>, float>> TimedEventContainer::s_ActiveEvents;
	std::vector<float> TimedEventContainer::s_ActiveEventTimes;
	std::vector<void*> TimedEventContainer::s_ActiveEventCallers;

	void TimedEventContainer::Update(float deltaTime)
	{
		// Go through all events
		for (size_t i = 0; i < s_ActiveEvents.size(); i++)
		{
			// Increment time
			s_ActiveEventTimes[i] += deltaTime;

			// If time has expired the event should be executed.
			if (s_ActiveEventTimes[i] > s_ActiveEvents[i].second)
			{
				// Execute event.
				s_ActiveEvents[i].first();

				// Delete event and timing.
				s_ActiveEventTimes.erase(s_ActiveEventTimes.begin() + i);
				s_ActiveEvents.erase(s_ActiveEvents.begin() + i);
				s_ActiveEventCallers.erase(s_ActiveEventCallers.begin() + i);
			}
		}
	}

	void TimedEventContainer::AddEvent(float timeUntillExecute, void* caller, std::function<void()> eventFunc)
	{
		// Add event and event timing.
		s_ActiveEvents.push_back({ eventFunc, timeUntillExecute });
		s_ActiveEventTimes.push_back(0);
		s_ActiveEventCallers.push_back(caller);
	}

	void TimedEventContainer::Reset()
	{
		s_ActiveEvents.clear();
		s_ActiveEventTimes.clear();
		s_ActiveEventCallers.clear();
	}

	void TimedEventContainer::DeleteCaller(void* caller)
	{
		// Delete matching caller and event.
		for (size_t i = 0; i < s_ActiveEventCallers.size(); i++)
		{
			if (caller == s_ActiveEventCallers[i])
			{
				s_ActiveEventTimes.erase(s_ActiveEventTimes.begin() + i);
				s_ActiveEvents.erase(s_ActiveEvents.begin() + i);
				s_ActiveEventCallers.erase(s_ActiveEventCallers.begin() + i);

				// Index decremented due to caller having multiple events potentially and make it so it does not skip.
				i--;
			}
		}
	}

	TimedEvent::TimedEvent(float time, void* caller, std::function<void()> eventFunc)
	{
		// Add event to TimedEventContainer.
		TimedEventContainer::AddEvent(time, caller, eventFunc);
	}
}