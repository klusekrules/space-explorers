// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BASETYPES_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BASETYPES_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

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

// This class is exported from the BaseTypes.dll
class BASETYPES_API CBaseTypes {
public:
	CBaseTypes(void);
	// TODO: add your methods here.
};

extern BASETYPES_API int nBaseTypes;

BASETYPES_API int fnBaseTypes(void);

#include <string>
using namespace std;
#include "BaseInterface.h"
#include "../Logger/LoggerInterface.h"

namespace SPG{
	/* Ogolne */
	typedef int					IdType; //+
	typedef unsigned int		Poziom; //+
	typedef float				Fluktuacja; //+
	typedef std::string			Tekst; //+
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
