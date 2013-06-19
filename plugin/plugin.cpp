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
#ifdef _WIN64
	if( (hFile = _findfirst( "plugins\\zmiana-x64\\*.dll", &c_file )) == -1L )
#else
	if( (hFile = _findfirst( "plugins\\zmiana\\*.dll", &c_file )) == -1L )
#endif
		lLogFile.info( "Brak plików *.dll w folderze pluginów!" );
	else
	{
		do {
			HMODULE hLibrary = LoadLibrary(c_file.name);
			if(hLibrary){
				lLogFile.info("Za³adowano biblioteke:");
				lLogFile.info(c_file.name);
				auto fun = (RejestrujZmiane)GetProcAddress(hLibrary,"RejestrujZmiane");
				if(fun){
					if(fun(zFabryka,lLogFile)){
						lLogFile.info("Za³adowano biblioteke:");
						lLogFile.info(c_file.name);
					}else{
						lLogFile.info("B³¹d ³adowania bilbioteki:");
						lLogFile.info(c_file.name);
					}
				}else{
					lLogFile.warn("Nie zanaleziono funkcji RejestrujZmiane.");
				}
			}else{
				lLogFile.warn("Nie za³adowano biblioteki:");
				lLogFile.warn(c_file.name);
			}
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