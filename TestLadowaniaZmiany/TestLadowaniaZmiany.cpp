// TestLadowaniaZmiany.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TestLadowaniaZmiany.h"


// This is an example of an exported variable
TESTLADOWANIAZMIANY_API int nTestLadowaniaZmiany=0;

// This is an example of an exported function.
TESTLADOWANIAZMIANY_API int fnTestLadowaniaZmiany(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see TestLadowaniaZmiany.h for the class definition
CTestLadowaniaZmiany::CTestLadowaniaZmiany()
{
	return;
}
