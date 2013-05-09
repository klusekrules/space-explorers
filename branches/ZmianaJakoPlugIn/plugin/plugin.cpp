// plugin.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "plugin.h"
#include "../Logger/LogLib.h"

typedef bool (*inicjalizacja)();

PLUGIN_API bool init(){
	inicjalizacja i;
	HMODULE hLibrary = LoadLibrary("FuncTransf-x86-d.dll");
	if(hLibrary){
		Log::getInstance().info("Za³adowano biblioteke FuncTransf-x86-d.dll");
		i = (inicjalizacja)GetProcAddress(hLibrary,"init");
		if( i ){
			return (*i)();
		}else{
			Log::getInstance().warn("Nie zanaleziono funkcji SymInitialize i/lub SymFromAddr.");
		}
	}else{
		Log::getInstance().warn("Nie za³adowano biblioteki Dbghelp.dll");
	}
	return false;
}