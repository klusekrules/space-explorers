#include "ListaPlikowRPC.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"
#include "Narzedzia\ZarzadcaZasobow.h"
#include "Narzedzia\SumaKontrolnaPliku.h"
#include "Kontroler\Zarzadca\ZarzadcaPluginow.h"
#include "StaleRPC.h"
#include "Utils\StaleUstawienAplikacji.h"

#define LISTA_PLIKOW "lista"
namespace SpEx{

	const std::string ListaPlikowRPC::NazwaTypu_ = "ListaPlikow";
	
	void ListaPlikowRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		odpowiedz[LISTA_PLIKOW] = Json::Value(Json::arrayValue);
		int a = 0;
		for( auto& zasob : Aplikacja::pobierzInstancje().pobierzZarzadcePluginow().pobierzListeSumKontrolnych()){
			odpowiedz[LISTA_PLIKOW][a++] = zasob->pobierzAdresPliku();
		}
		odpowiedz[LISTA_PLIKOW][a++] = Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()[ATRYBUT_PLIK_DANYCH];
	}

	bool ListaPlikowRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		if (odpowiedz[LISTA_PLIKOW].isArray()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Lista plików:");
			}
			for (auto & element : odpowiedz[LISTA_PLIKOW]){				
				if (element.isString()){
					listaPlikow_.emplace_back(element.asString());
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, element.asString());
					}
				}
			}
			return true;
		}
		return false; 
	}

	const std::vector<std::string>& ListaPlikowRPC::pobierzListePlikow() const{
		return listaPlikow_;
	}

	std::string ListaPlikowRPC::napis() const{
		SLog::Logger logger(NAZWAKLASY(ListaPlikowRPC));
		logger.dodajKlase(MetodaRPC::napis());
		return logger.napis();
	}
}
