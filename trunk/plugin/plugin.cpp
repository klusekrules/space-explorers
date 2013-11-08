#include "plugin.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "..\FuncTransf\ZmianaLiniowa.h"
#include "..\FuncTransf\ZmianaPotegowa.h"
#include "..\FuncTransf\ZmianaAgregacja.h"
#include "..\FuncTransf\ZmianaPotegowaAlt.h"
#include <io.h>

Cplugin::Cplugin( const std::string& folderPluginow, ZmianaFabryka& fabryka , Log& log )
	: fabryka_(fabryka), log_(log) , folderPluginow_(folderPluginow)
{
}

bool Cplugin::zaladujZewnetrzneKlasyZmian(){
	struct _finddata_t plik;
	intptr_t uchwytPliku;
	std::string folder;
	std::string rozszezenie;
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
		log_.loguj(Log::Info, "Brak plików *.dll w folderze pluginów!" );
	else
	{
		do {
			HMODULE uchwytBiblioteki = LoadLibrary((folder+plik.name).c_str());
			if(uchwytBiblioteki){
				auto fun = (ZmianaFabryka::RejestrujZmiane)GetProcAddress( uchwytBiblioteki, "RejestrujZmiany" );
				if(fun){
					if(fun( fabryka_, log_ )){
						log_.loguj(Log::Info,"Za³adowano biblioteke:");
						log_.loguj(Log::Info,plik.name);
					}else{
						log_.loguj(Log::Info,"B³¹d ³adowania bilbioteki:");
						log_.loguj(Log::Info,plik.name);
					}
				}else{
					log_.loguj(Log::Warning,"Nie zanaleziono funkcji RejestrujZmiane.");
				}
			}else{
				log_.loguj(Log::Warning,"Nie za³adowano biblioteki:");
				log_.loguj(Log::Warning,plik.name);
			}
		} while( _findnext( uchwytPliku, &plik ) == 0 );
		_findclose( uchwytPliku );
	}
	return true;
}

bool Cplugin::zaladujDomyslneKlasyZmian(){
	bool rezultat = true;
	if(!ZmianaAgregacja::RejestrujZmianaAgregacja(fabryka_)){
		log_.loguj(Log::Debug,"Nie zarejestrowano zmiany:");
		log_.loguj(Log::Debug,NAZWAKLASY(ZmianaAgregacja));
		rezultat=false;
	}
	if(!ZmianaLiniowa::RejestrujZmianaLiniowa(fabryka_)){
		log_.loguj(Log::Debug,"Nie zarejestrowano zmiany:");
		log_.loguj(Log::Debug,NAZWAKLASY(ZmianaLiniowa));
		rezultat=false;
	}
	if(!ZmianaPotegowa::RejestrujZmianaPotegowa(fabryka_)){
		log_.loguj(Log::Debug,"Nie zarejestrowano zmiany:");
		log_.loguj(Log::Debug,NAZWAKLASY(ZmianaPotegowa));
		rezultat=false;
	}
	if(!ZmianaPotegowaAlt::RejestrujZmianaPotegowaAlt(fabryka_)){
		log_.loguj(Log::Debug,"Nie zarejestrowano zmiany:");
		log_.loguj(Log::Debug,NAZWAKLASY(ZmianaPotegowa));
		rezultat=false;
	}
	return rezultat;
}