#include "SprawdzSumyKontrolneRPC.h"
#include "Logger\Logger.h"

namespace SpEx{

	const std::string SprawdzSumyKontrolneRPC::NazwaTypu_ = "SprawdzSumyKontrolne";
	
	std::shared_ptr<MetodaRPC> SprawdzSumyKontrolneRPC::TworzObiekt(const Json::Value & metoda, Klient& klient){
		auto ptr = std::make_shared<SprawdzSumyKontrolneRPC>(klient);
		if (metoda.isNull()){
			// Tworzenie nowej pustej metody, do wys�ania na serwer
		} else{
			if ((*ptr) << metoda){
				// Uda�o si� odtworzy� metod�, przypisanie parametr�w wymaganych przez metod� do atrybut�w metody.
			} else{
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod�a si� deserializacja metody ZalogujRPC.");
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
