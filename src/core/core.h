// 2022 Tygo Boons

#pragma once

#include <Windows.h>
#include <iostream>


// Throw error if not compiled in windows.
#if !defined(_WIN32) && !defined(WIN64)
#error This project only supports Windows
#endif


// Initialize logging system if in debug mode.
#ifdef _DEBUG
#define LOG_INIT
#endif


// Setup Console logging and Asserting.
#ifdef _DEBUG

#include "Utils/Log.h"

#define LOG(message) LOG_TRACE(message);
#define LOG_TRACE(message) Utils::Log::LogMessage(Utils::Log::LogColor::White, std::string("[TRACE] ") + message);
#define LOG_INFO(message)  Utils::Log::LogMessage(Utils::Log::LogColor::Green, std::string("[INFO]  ")  + message);
#define LOG_WARN(message)  Utils::Log::LogMessage(Utils::Log::LogColor::Yellow, std::string("[WARN]  ") + message);
#define LOG_ERROR(message) Utils::Log::LogMessage(Utils::Log::LogColor::Red, std::string("[ERROR] ")   + message);

#define ASSERT(condition, message)\
                                    if(!(condition))\
                                    {\
                                        Utils::Log::LogMessage(Utils::Log::LogColor::WhiteOnRed, std::string("[ASSERT] ") + message);\
                                        DebugBreak();\
                                    }

#else
#define LOG(message) ;;
#define LOG_TRACE(message) ;;
#define LOG_INFO(message) ;;
#define LOG_WARN(message) ;;
#define LOG_ERROR(message);
#define ASSERT(condition, message) ;;

#endif


// Simple to_string macro.
#include <string>
#define TOTEXT(value) std::to_string(value)


// Simplify the shared and unique ptr names.
#include <memory>
    
template<class T>
using ScopePtr = std::unique_ptr<T>;

template<class T>
using RefPtr = std::shared_ptr<T>;


// Macros to simplify shared ptr creation of a class instance.
#define MAKE_SHARED(type)\
    public:\
        static RefPtr<type> Create()\
        {\
            return std::make_shared<type>();\
        }

#define MAKE_SHARED_ONEPARAM(type, paramtype, paramname)\
    public:\
        static RefPtr<type> Create(paramtype paramname)\
        {\
            return std::make_shared<type>(paramname);\
        }

#define MAKE_SHARED_TWOPARAM(type, param1type, param1name, param2type, param2name)\
 	public:\
        static RefPtr<type> Create(param1type param1name, param2type param2name)\
        {\
            return std::make_shared<type>(param1name, param2name);\
        }