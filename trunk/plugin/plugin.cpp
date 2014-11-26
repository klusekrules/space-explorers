#include "plugin.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#include "Zmiana\ZmianaAgregacja.h"
#include "Zmiana\ZmianaLiniowa.h"
#include "Zmiana\ZmianaLiniowaIlosciowa.h"
#include "Zmiana\ZmianaPotegowa.h"
#include "Zmiana\ZmianaPotegowaAlt.h"
#include "Zmiana\ZmianaStaleNapisy.h"
#include "PluginStale.h"
#include "Logger\Logger.h"

namespace SPlu{
	Cplugin::Cplugin(const std::string& folderPluginow, SZmi::ZmianaFabryka& fabryka, SLog::Log& log)
		: fabryka_(fabryka), log_(log), folderPluginow_(folderPluginow)
	{
	}

	bool Cplugin::zaladujZewnetrzneKlasyZmian(){
		struct _finddata_t plik;
		intptr_t uchwytPliku;
		std::string folder;
		std::string rozszezenie;
#ifdef _WIN64
		folder= folderPluginow_ + PLUGIN_FOLDER_X64;
#else
		folder = folderPluginow_ + PLUGIN_FOLDER_X86;
#endif

#ifdef _DEBUG
		rozszezenie=PLUGIN_PLIK_DEBUG;
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
						}
						else{
#ifndef LOG_OFF_ALL
							log_.loguj(SLog::Log::Info, PLUGIN_BLAD_LADOWANIA_ZMIANY);
							log_.loguj(SLog::Log::Info, plik.name);
#endif
						}
					}
					else{
#ifndef LOG_OFF_ALL
						log_.loguj(SLog::Log::Warning, PLUGIN_NIE_ZNALEZIONO_ZMIANY);
#endif
					}
				}
				else{
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

	bool Cplugin::zaladujDomyslneKlasyZmian(){
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

	std::string Cplugin::napis() const{
		SLog::Logger logger(NAZWAKLASY(Cplugin));
		logger.dodajPole(NAZWAKLASY(folderPluginow_), NAZWAKLASY2(folderPluginow_), folderPluginow_);
		return logger.napis();
	}
}
