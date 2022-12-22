// Tygo Boons 2022

#include "mypch.h"

#include "ThreadHelper.h"

namespace Utils
{
	RefPtr<std::thread> ThreadHelper::CreateThread(std::function<void()> func)
	{
		// Create new thread with function.
		RefPtr<std::thread> newThread = std::make_shared<std::thread>(new std::thread(func));

		// Add thread to threads vector.

		s_Threads.push_back(newThread);
		return newThread;
	}
}