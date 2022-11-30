// 2022 Tygo Boons

#pragma once

#include <Windows.h>
#include <iostream>

#if !defined(_WIN32) && !defined(WIN64)
#error This project only supports Windows
#endif

#ifdef _DEBUG

#define ALLOC_CONSOLE() __pragma(warning(push))          \
                        __pragma(warning(disable:6031))  \
                        AllocConsole();                  \
                        freopen("CONOUT$", "w", stdout); \
                        __pragma (warning(pop))
#else
#define ALLOC_CONSOLE() ;;
#endif

#ifdef _DEBUG
#define LOG(message) std::cout << "LOG: " << message << '\n';
#define LOG_ERROR(message) std::cout << "ERROR: " << message << '\n';
#define ASSERT(condition, message)  if(!(condition))                                \
                                    {                                               \
                                        std::cout << "ASSERT: " << message << '\n'; \
                                        DebugBreak();                               \
                                    }

#else
#define LOG(message) ;;
#define LOG_ERROR(message) ;;
#define ASSERT(condition, message) ;;
#endif


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