#include "ListaPlikowRPC.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Zarzadca\ZarzadcaZasobow.h"
#include "Kontroler\Zarzadca\SumaKontrolnaPliku.h"
#include "Kontroler\Zarzadca\ZarzadcaPluginow.h"
#include "StaleRPC.h"
#include "Utils\StaleUstawienAplikacji.h"

#define LISTA_PLIKOW "lista"
namespace SpEx{

	const std::string ListaPlikowRPC::NazwaTypu_ = "ListaPlikow";
	
	void ListaPlikowRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		
	}

	bool ListaPlikowRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		if (odpowiedz[LISTA_PLIKOW].isArray()){
			for (auto & element : odpowiedz[LISTA_PLIKOW]){
				if (element.isString()){
					listaPlikow_.emplace_back(element.asString());
				}
			}
			return true;
		}
		return false; 
	}

	std::string ListaPlikowRPC::napis() const{
		SLog::Logger logger(NAZWAKLASY(ListaPlikowRPC));
		logger.dodajKlase(MetodaRPC::napis());
		return logger.napis();
	}
}
