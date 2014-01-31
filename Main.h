#pragma once
#pragma warning( disable : 4290 )
//#pragma warning( disable : 4996 )

//Deklaracja w³¹czaj¹ca/wy³¹czaj¹ca testy
#define TESTS

#ifdef TESTS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <string>

#include "Logger\Log.h"