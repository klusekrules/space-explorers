#pragma once
#pragma warning( disable : 4290 )
//#pragma warning( disable : 4996 )

//Deklaracja w��czaj�ca/wy��czaj�ca testy
#define TESTS

#ifdef TESTS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

using namespace std;
#include <string>

#include "Logger\Log.h"