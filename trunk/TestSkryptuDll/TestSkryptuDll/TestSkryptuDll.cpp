#include "stdafx.h"
#include "TestSkryptuDll.h"

extern "C" __declspec(dllimport) void __cdecl zamknijAplikacje();
extern "C" __declspec(dllimport) void __cdecl loguj(const char *komunikat);

extern "C" TESTSKRYPTUDLL_API int zamknijAplikacjeSkryptDll(void)
{
	loguj("U¿ycie skryptu dll do zamykania aplikacji.");
	zamknijAplikacje();
	return 0;
}

