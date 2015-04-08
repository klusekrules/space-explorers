#include "EchoRPC.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"

namespace SpEx{

	const std::string EchoRPC::NazwaTypu_ = "Echo";

	void EchoRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){

		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Echo na serwerze.");
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Serwer: parametry_[\"Echo\"] = " + parametry_["Echo"].asString());
		}

		parametry_["Echo"] = "Do klienta";
		odpowiedz["rezultat"] = "Odpowiedü serwera na komunikat Echo.";		
	}

	bool EchoRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		auto value = odpowiedz["rezultat"];

		if (!parametry_["Echo"].empty()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Klient: parametry_[\"Echo\"] = " + parametry_["Echo"].asString());
			}
		}

		if (value.isString()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Komunikat Echo: " + value.asString());
			}
			return true;
		}else{
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Niepoprawna odpowiedü na komunikat Echo.");
			}
			return false;
		}
	}

	std::string EchoRPC::napis() const{
		SLog::Logger log(NAZWAKLASY(EchoRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}

}
