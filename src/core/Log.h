// 2022 Tygo Boons
// Taken from other project I created:
// https://github.com/TygoB-B5/BEngine/blob/Engine/Engine/Src/Utils/Log.h

#pragma once

// Define LOG_INIT to initialize logging system.
// #define LOG_INIT

namespace Utils
{
	class Log
	{
	public:

		// Type define tm to LocalTime to make code more readable.
		typedef tm LocalTime;

		// Types of logs that are possible to log
		// LogColor values are the windows console color id's.
		enum class LogColor
		{
			White = 0x0F | 0,
			Blue = 0x03 | 0,
			Green = 0x02 | 0,
			Red = 0x04 | 0,
			Purple = 0x05 | 0,
			Yellow = 0x06 | 0,
			WhiteOnRed = 0x0F | 0x0040,
		};

		Log();

		// Logs a message in the console with a specified LogType.
		static void LogMessage(LogColor type, const std::string& message)
		{
#ifdef LOG_INIT
			s_Instance->LogMessageImpl(type, message);
#endif
		}

	private:

		// Member implementation of LogMessage
		void LogMessageImpl(LogColor type, const std::string& message);

		// Formats the time values so they look pretty.
		inline std::string FormatTime(uint32_t year, uint32_t month, uint32_t day, uint32_t hour, uint32_t minutes, uint32_t seconds, uint32_t milliseconds);
		
		// Return LocalTime object with local time variables.
		inline LocalTime GetSystemTime(const std::chrono::system_clock::time_point& timePoint);

		// Returns the amount of milliseconds that have passed in the current second.
		inline uint32_t GetMillisecondsInCurrentSecond(const std::chrono::system_clock::time_point& timePoint);

	private:

		// Singleton
		static Log* s_Instance;

		std::mutex m_Mutex;
		LogColor m_LastLogColor;
		HANDLE m_ConsoleHandle;
	};
}