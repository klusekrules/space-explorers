#include "stdafx.h"
#include "plugin.h"

#include "..\FuncTransf\ZmianaLiniowa.h"
#include "..\FuncTransf\ZmianaPotegowa.h"
#include "..\FuncTransf\ZmianaAgregacja.h"
#include "..\FuncTransf\ZmianaDekorator.h"

#include <io.h>

Cplugin::Cplugin( ZmianaFabryka& ref, Log& logFile )
	: zFabryka(ref), lLogFile(logFile)
{
}

bool Cplugin::LoadPluginsZmiana(){
	struct _finddata_t c_file;
	intptr_t hFile;

	if( (hFile = _findfirst( "plugins\\*.dll", &c_file )) == -1L )
		lLogFile.info( "No *.dll files in plugins directory!\n" );
	else
	{
		do {
			lLogFile.info( c_file.name );
		} while( _findnext( hFile, &c_file ) == 0 );
		_findclose( hFile );
	}
	return true;
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