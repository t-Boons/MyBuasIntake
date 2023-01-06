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
				// Run if caller is still alive.
				if (s_ActiveEventCallers[i] != nullptr)
				{
					// Execute event.
					s_ActiveEvents[i].first();
				}
				else
				{
					LOG_ERROR("TIMEDEVENT: Event caller was nullptr")
				}

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

	TimedEvent::TimedEvent(float time, void* caller, std::function<void()> eventFunc)
	{
		// Add event to TimedEventContainer.
		TimedEventContainer::AddEvent(time, caller, eventFunc);
	}
}