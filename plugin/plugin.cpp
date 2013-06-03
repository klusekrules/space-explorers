#include "stdafx.h"
#include "plugin.h"

#include "..\FuncTransf\ZmianaLiniowa.h"
#include "..\FuncTransf\ZmianaPotegowa.h"
#include "..\FuncTransf\ZmianaAgregacja.h"
#include "..\FuncTransf\ZmianaDekorator.h"

Cplugin::Cplugin( ZmianaFabryka& ref, Log& logFile )
	: zFabryka(ref), lLogFile(logFile)
{
}

bool Cplugin::LoadDefaultZmiana(){
	bool result = true;
	if(!ZmianaDekorator::RejestrujZmianaDekotor(zFabryka)){
		lLogFile.debug("Nie zarejestrowano zmiany:");
		lLogFile.debug(CLASSNAME(ZmianaDekorator));
		result=false;
	} 
	if(!ZmianaAgregacja::RejestrujZmianaAgregacja(zFabryka)){
		lLogFile.debug("Nie zarejestrowano zmiany:");
		lLogFile.debug(CLASSNAME(ZmianaAgregacja));
		result=false;
	}
	if(!ZmianaLiniowa::RejestrujZmianaLiniowa(zFabryka)){
		lLogFile.debug("Nie zarejestrowano zmiany:");
		lLogFile.debug(CLASSNAME(ZmianaLiniowa));
		result=false;
	}
	if(!ZmianaPotegowa::RejestrujZmianaPotegowa(zFabryka)){
		lLogFile.debug("Nie zarejestrowano zmiany:");
		lLogFile.debug(CLASSNAME(ZmianaPotegowa));
		result=false;
	}
	return result;
}