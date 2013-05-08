// BaseTypes.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "BaseTypes.h"


// This is an example of an exported variable
BASETYPES_API int nBaseTypes=0;

// This is an example of an exported function.
BASETYPES_API int fnBaseTypes(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see BaseTypes.h for the class definition
CBaseTypes::CBaseTypes()
{
	return;
}
