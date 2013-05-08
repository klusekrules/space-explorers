// FuncTransf.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "FuncTransf.h"


// This is an example of an exported variable
FUNCTRANSF_API int nFuncTransf=0;

// This is an example of an exported function.
FUNCTRANSF_API int fnFuncTransf(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see FuncTransf.h for the class definition
CFuncTransf::CFuncTransf()
{
	return;
}
