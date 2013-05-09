// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#ifdef FABRTRANSF_EXPORTS
#define FABRTRANSF_API __declspec(dllexport)
#else
#define FABRTRANSF_API __declspec(dllimport)
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "fabtrans-x64-d" )
#else if _WIN32
#pragma comment( lib, "fabtrans-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "fabtrans-x64" )
#else if _WIN32
#pragma comment( lib, "fabtrans-x86" )
#endif
#endif
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here
