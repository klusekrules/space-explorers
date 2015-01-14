#include "EchoRPC.h"
#include "Logger\Logger.h"

namespace SpEx{

	bool EchoRPC::RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger){
		return fabryka.rejestracjaMetodyRPC(STyp::Tekst("Echo"), EchoRPC::TworzObiekt);
	}

	std::unique_ptr<MetodaRPC> EchoRPC::TworzObiekt(const Json::Value & metoda, Klient& klient){
		auto ptr = std::make_unique<EchoRPC>(klient);
		if (metoda.isNull()){
			// Dodanie wszystkich niezbêdnych danych.
			ptr->nazwa_ = "Echo";
			ptr->powtorzenie_ = 0;
			ptr->id_unikalne_ = "1";
		} else{
			if ((*ptr) << metoda){
				// Uda³o siê odtworzyæ metodê, przypisanie parametrów wymaganych przez metodê do atrybutów metody.
			} else{
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod³a siê deserializacja metody Echo.");
			}
		}
		return std::move(ptr);
	}


	EchoRPC::EchoRPC(const PolaczenieTCP& polaczenie)
		: MetodaRPC(polaczenie)
	{
	}

	void EchoRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		odpowiedz["rezultat"] = " OdpowiedŸ serwera na komunikat Echo.";
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Echo na serwerze.");
	}

	bool EchoRPC::inicjalizacjaParametrow(){
		return true;
	}

	bool EchoRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		auto value = odpowiedz["rezultat"];
		if (value.isString()){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Komunikat Echo: " + value.asString());
			return true;
		}else{
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Niepoprawna odpowiedŸ na komunikat Echo.");
			return false;
		}
	}

	std::string EchoRPC::napis() const{
		SLog::Logger log(NAZWAKLASY(EchoRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}

}
