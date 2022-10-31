// Copyright (C) 2022 Tygo Boons
// All rights reserved.

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
#define LOG(message) std::cout << "Log: " << message << '\n';

#define ASSERT(condition, message)  if(!(condition))                                \
                                    {                                               \
                                        std::cout << "Assert: " << message << '\n'; \
                                        DebugBreak();                               \
                                    }

#else
#define LOG(message) ;;
#define ASSERT(condition, message) ;;
#endif