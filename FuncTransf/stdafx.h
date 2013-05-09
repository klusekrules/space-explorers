// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef FUNCTRANSF_EXPORTS
#define FUNCTRANSF_API __declspec(dllexport)
#else
#define FUNCTRANSF_API __declspec(dllimport)
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "ftrans-x64-d" )
#else if _WIN32
#pragma comment( lib, "ftrans-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "ftrans-x64" )
#else if _WIN32
#pragma comment( lib, "ftrans-x86" )
#endif
#endif
#endif

#pragma warning( disable : 4290 )
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here
