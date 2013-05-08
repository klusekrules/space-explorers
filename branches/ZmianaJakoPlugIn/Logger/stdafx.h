// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "logger-x64-d" )
#else if _WIN32
#pragma comment( lib, "logger-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "logger-x64" )
#else if _WIN32
#pragma comment( lib, "logger-x86" )
#endif
#endif
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here
