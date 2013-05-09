// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef BASETYPES_EXPORTS
#define BASETYPES_API __declspec(dllexport)
#else
#define BASETYPES_API __declspec(dllimport)
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "BaseTypes-x64-d" )
#else if _WIN32
#pragma comment( lib, "BaseTypes-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "BaseTypes-x64" )
#else if _WIN32
#pragma comment( lib, "BaseTypes-x86" )
#endif
#endif
#endif

#pragma warning( disable : 4251 )
#pragma warning( disable : 4290 )

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <string>
using namespace std;
#include "BaseInterface.h"
#include "../Logger/LoggerInterface.h"

namespace SPG{
	/* Ogolne */
	typedef int					IdType; //+
	typedef unsigned int		Poziom; //+
	typedef float				Fluktuacja; //+
	typedef string				Tekst; //+
	typedef long double			IloscJednostek; //+
	typedef double				Objetosc; //+
	typedef double				Masa; //+
	typedef double				Dystans; //+
	typedef double				Predkosc; //+
	typedef double				Powierzchnia; //+
	typedef double				Parametr;//+
	
	/* Flota */
	typedef double	Obrazenia; //+
	typedef double	ZuzyciePaliwa; //+
	typedef double	MocSilnika; //+
}

// TODO: reference additional headers your program requires here
