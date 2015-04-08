#include "stdafx.h"
#include "TestSkryptuDll.h"
#include "Export.h"

extern "C" TESTSKRYPTUDLL_API int zamknijAplikacjeSkryptDll(void)
{
	loguj("U¿ycie skryptu dll do zamykania aplikacji.");
	zamknijAplikacje();
	return 0;
}

