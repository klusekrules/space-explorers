#include "Plugin.h"
#include <windows.h>
#include <io.h>
#include "Zmiana\ZmianaAgregacja.h"
#include "Zmiana\ZmianaLiniowa.h"
#include "Zmiana\ZmianaLiniowaIlosciowa.h"
#include "Zmiana\ZmianaPotegowa.h"
#include "Zmiana\ZmianaPotegowaAlt.h"
#include "Zmiana\ZmianaStaleNapisy.h"
#include "Logger\Logger.h"

#define PLUGIN_BRAK_PLIKOW_ZMIAN "Brak plików *.dll w folderze pluginów!"
#define PLUGIN_ZALADOWANO_ZMIANE "Za³adowano biblioteke:"
#define PLUGIN_BLAD_LADOWANIA_ZMIANY "B³¹d ³adowania bilbioteki:"
#define PLUGIN_NIE_ZNALEZIONO_ZMIANY "Nie zanaleziono funkcji RejestrujZmiane."
#define PLUGIN_NIE_ZALADOWANO_ZMIANY "Nie za³adowano biblioteki:"
#define PLUGIN_NIE_ZAREJESTROWANO_ZMIANY "Nie zarejestrowano zmiany:"

#define PLUGIN_FOLDER_X86 "zmiana\\"
#define PLUGIN_FOLDER_X64 "zmiana-x64\\"
#define PLUGIN_PLIK_DEBUG "*-d.dll"
#define PLUGIN_PLIK_RELEASE "*-r.dll"


namespace SpEx{

	Plugin::Plugin(const UstawieniaAplikacji& ustawienia, SZmi::ZmianaFabryka& fabryka, SLog::Log& log)
		: fabryka_(fabryka), log_(log), folderPluginow_(ustawienia[ATRYBUT_FOLDER_PLUGINOW])
	{
	}

	bool Plugin::zaladujZewnetrzneKlasyZmian(){
		struct _finddata_t plik;
		intptr_t uchwytPliku;
		std::string folder;
		std::string rozszezenie;
#ifdef _WIN64
		folder = folderPluginow_ + PLUGIN_FOLDER_X64;
#else
		folder = folderPluginow_ + PLUGIN_FOLDER_X86;
#endif

#ifdef _DEBUG
		rozszezenie = PLUGIN_PLIK_DEBUG;
#else
		rozszezenie = PLUGIN_PLIK_RELEASE;
#endif
		if ((uchwytPliku = _findfirst((folder + rozszezenie).c_str(), &plik)) == -1L)
#ifndef LOG_OFF_ALL
			log_.loguj(SLog::Log::Info, PLUGIN_BRAK_PLIKOW_ZMIAN);
#endif
		else
		{
			do {
				HMODULE uchwytBiblioteki = LoadLibrary((folder + plik.name).c_str());
				if (uchwytBiblioteki){
					auto fun = (SZmi::ZmianaFabryka::RejestrujZmiane)GetProcAddress(uchwytBiblioteki, ZMIANA_NAZWA_FUNKCJI_LADUJACEJ_KLASY_ZMIAN);
					if (fun){
						if (fun(fabryka_, log_)){
#ifndef LOG_OFF_ALL
							log_.loguj(SLog::Log::Info, PLUGIN_ZALADOWANO_ZMIANE);
							log_.loguj(SLog::Log::Info, plik.name);
#endif
						} else{
#ifndef LOG_OFF_ALL
							log_.loguj(SLog::Log::Info, PLUGIN_BLAD_LADOWANIA_ZMIANY);
							log_.loguj(SLog::Log::Info, plik.name);
#endif
						}
					} else{
#ifndef LOG_OFF_ALL
						log_.loguj(SLog::Log::Warning, PLUGIN_NIE_ZNALEZIONO_ZMIANY);
#endif
					}
				} else{
#ifndef LOG_OFF_ALL
					log_.loguj(SLog::Log::Warning, PLUGIN_NIE_ZALADOWANO_ZMIANY);
					log_.loguj(SLog::Log::Warning, plik.name);
#endif
				}
			} while (_findnext(uchwytPliku, &plik) == 0);
			_findclose(uchwytPliku);
		}
		return true;
	}

	bool Plugin::zaladujDomyslneKlasyZmian(){
		bool rezultat = true;
		if (!SZmi::ZmianaAgregacja::RejestrujZmianaAgregacja(fabryka_)){
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
			log_.loguj(SLog::Log::Debug, PLUGIN_NIE_ZAREJESTROWANO_ZMIANY);
			log_.loguj(SLog::Log::Debug, NAZWAKLASY(SZmi::ZmianaAgregacja));
#endif
			rezultat = false;
		}
		if (!SZmi::ZmianaLiniowa::RejestrujZmianaLiniowa(fabryka_)){
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
			log_.loguj(SLog::Log::Debug, PLUGIN_NIE_ZAREJESTROWANO_ZMIANY);
			log_.loguj(SLog::Log::Debug, NAZWAKLASY(SZmi::ZmianaLiniowa));
#endif
			rezultat = false;
		}
		if (!SZmi::ZmianaLiniowaIlosciowa::RejestrujZmianaLiniowaIlosciowa(fabryka_)){
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
			log_.loguj(SLog::Log::Debug, PLUGIN_NIE_ZAREJESTROWANO_ZMIANY);
			log_.loguj(SLog::Log::Debug, NAZWAKLASY(SZmi::ZmianaLiniowaIlosciowa));
#endif
			rezultat = false;
		}
		if (!SZmi::ZmianaPotegowa::RejestrujZmianaPotegowa(fabryka_)){
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
			log_.loguj(SLog::Log::Debug, PLUGIN_NIE_ZAREJESTROWANO_ZMIANY);
			log_.loguj(SLog::Log::Debug, NAZWAKLASY(SZmi::ZmianaPotegowa));
#endif
			rezultat = false;
		}
		if (!SZmi::ZmianaPotegowaAlt::RejestrujZmianaPotegowaAlt(fabryka_)){
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
			log_.loguj(SLog::Log::Debug, PLUGIN_NIE_ZAREJESTROWANO_ZMIANY);
			log_.loguj(SLog::Log::Debug, NAZWAKLASY(SZmi::ZmianaPotegowa));
#endif
			rezultat = false;
		}
		return rezultat;
	}

	std::string Plugin::napis() const{
		SLog::Logger logger(NAZWAKLASY(Plugin));
		logger.dodajPole(NAZWAKLASY(folderPluginow_), NAZWAKLASY2(folderPluginow_), folderPluginow_);
		return logger.napis();
	}

}
