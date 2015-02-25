#include "ZalogujRPC.h"
#include "Fabrykator.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"

namespace SpEx{
	ZalogujRPC::ZalogujRPC(Klient& gniazdo)
		: MetodaRPC(gniazdo)
	{
	}

	bool ZalogujRPC::RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger){
		return fabryka.rejestracjaMetodyRPC(STyp::Tekst("Zaloguj"), ZalogujRPC::TworzObiekt);
	}

	std::shared_ptr<MetodaRPC> ZalogujRPC::TworzObiekt(const Json::Value & metoda, Klient& klient){
		auto ptr = std::make_shared<ZalogujRPC>(klient);
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
	
	void ZalogujRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz) {
	}
	
	bool ZalogujRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz) {
		return false;
	}

	std::string ZalogujRPC::napis() const {
		SLog::Logger log(NAZWAKLASY(ZalogujRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}
}