#include "SprawdzSumyKontrolneRPC.h"
#include "Logger\Logger.h"

namespace SpEx{

	const std::string SprawdzSumyKontrolneRPC::NazwaTypu_ = "SprawdzSumyKontrolne";
	
	std::shared_ptr<MetodaRPC> SprawdzSumyKontrolneRPC::TworzObiekt(const Json::Value & metoda, Klient& klient){
		auto ptr = std::make_shared<SprawdzSumyKontrolneRPC>(klient);
		if (metoda.isNull()){
			// Tworzenie nowej pustej metody, do wys³ania na serwer
		} else{
			if ((*ptr) << metoda){
				// Uda³o siê odtworzyæ metodê, przypisanie parametrów wymaganych przez metodê do atrybutów metody.
			} else{
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod³a siê deserializacja metody ZalogujRPC.");
				return nullptr;
			}
		}
		return std::move(ptr);
	}

	std::string SprawdzSumyKontrolneRPC::napis() const{
		SLog::Logger logger(NAZWAKLASY(SprawdzSumyKontrolneRPC));
		logger.dodajKlase(MetodaRPC::napis());
		return logger.napis();
	}

	void SprawdzSumyKontrolneRPC::obslugaZadania(const Json::Value &, Json::Value&){}

	bool SprawdzSumyKontrolneRPC::obslugaOdpowiedzi(const Json::Value &){
		return false;
	}
}
