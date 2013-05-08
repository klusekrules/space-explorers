// plugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "plugin.h"


// This is an example of an exported variable
PLUGIN_API int nplugin=0;

// This is an example of an exported function.
PLUGIN_API int fnplugin(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see plugin.h for the class definition
Cplugin::Cplugin()
{
	return;
}
