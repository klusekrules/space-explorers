#include "plugin.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "..\FuncTransf\ZmianaLiniowa.h"
#include "..\FuncTransf\ZmianaPotegowa.h"
#include "..\FuncTransf\ZmianaAgregacja.h"
#include "..\FuncTransf\ZmianaPotegowaAlt.h"
#include <io.h>

Cplugin::Cplugin( const string& folderPluginow, ZmianaFabryka& fabryka , Log& log )
	: fabryka_(fabryka), log_(log) , folderPluginow_(folderPluginow)
{
}

bool Cplugin::zaladujZewnetrzneKlasyZmian(){
	struct _finddata_t plik;
	intptr_t uchwytPliku;
	string folder;
	string rozszezenie;
#ifdef _WIN64
	folder= folderPluginow_ + "zmiana-x64\\";
#else
	folder= folderPluginow_ + "zmiana\\";
#endif
#ifdef DEBUG
	rozszezenie="*-d.dll";
#else
	rozszezenie="*-r.dll";
#endif
	if( (uchwytPliku = _findfirst( (folder+rozszezenie).c_str() , &plik )) == -1L )
		log_.info( "Brak plików *.dll w folderze pluginów!" );
	else
	{
		do {
			HMODULE uchwytBiblioteki = LoadLibrary((folder+plik.name).c_str());
			if(uchwytBiblioteki){
				auto fun = (ZmianaFabryka::RejestrujZmiane)GetProcAddress( uchwytBiblioteki, "RejestrujZmiany" );
				if(fun){
					if(fun( fabryka_, log_ )){
						log_.info("Za³adowano biblioteke:");
						log_.info(plik.name);
					}else{
						log_.info("B³¹d ³adowania bilbioteki:");
						log_.info(plik.name);
					}
				}else{
					log_.warn("Nie zanaleziono funkcji RejestrujZmiane.");
				}
			}else{
				log_.warn("Nie za³adowano biblioteki:");
				log_.warn(plik.name);
			}
		} while( _findnext( uchwytPliku, &plik ) == 0 );
		_findclose( uchwytPliku );
	}
	return true;
}

bool Cplugin::zaladujDomyslneKlasyZmian(){
	bool rezultat = true;
	if(!ZmianaAgregacja::RejestrujZmianaAgregacja(fabryka_)){
		log_.debug("Nie zarejestrowano zmiany:");
		log_.debug(CLASSNAME(ZmianaAgregacja));
		rezultat=false;
	}
	if(!ZmianaLiniowa::RejestrujZmianaLiniowa(fabryka_)){
		log_.debug("Nie zarejestrowano zmiany:");
		log_.debug(CLASSNAME(ZmianaLiniowa));
		rezultat=false;
	}
	if(!ZmianaPotegowa::RejestrujZmianaPotegowa(fabryka_)){
		log_.debug("Nie zarejestrowano zmiany:");
		log_.debug(CLASSNAME(ZmianaPotegowa));
		rezultat=false;
	}
	if(!ZmianaPotegowaAlt::RejestrujZmianaPotegowaAlt(fabryka_)){
		log_.debug("Nie zarejestrowano zmiany:");
		log_.debug(CLASSNAME(ZmianaPotegowa));
		rezultat=false;
	}
	return rezultat;
}