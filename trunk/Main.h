#pragma once
#pragma warning( disable : 4290 )
//#pragma warning( disable : 4996 )
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment( lib, "ticpp-x64-d" )
#else if _WIN32
#pragma comment( lib, "ticpp-x86-d" )
#endif
#else
#ifdef _WIN64
#pragma comment( lib, "ticpp-x64" )
#else if _WIN32
#pragma comment( lib, "ticpp-x86" )
#endif
#endif

#pragma comment( lib, "allegro-debug" )

//Deklaracja w³¹czaj¹ca/wy³¹czaj¹ca testy
#define TESTS

//Makro wstawiajace nazwe pliku i liniê i datê pliku.
#define EXCEPTION_PLACE Tekst(__FILE__) , IdType(__LINE__)

#include "Constants.h"

#ifdef TESTS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

using namespace std;
#include <string>

#include "LoggerInterface.h"
#include "Log.h"