#pragma once
#pragma warning( disable : 4290 )
//#pragma warning( disable : 4996 )
#pragma comment( lib, "ticppd" )
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