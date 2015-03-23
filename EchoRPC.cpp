#include "EchoRPC.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"

namespace SpEx{

	const std::string EchoRPC::NazwaTypu_ = "Echo";

	void EchoRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		parametry_["Echo"] = "Do klienta";
		odpowiedz["rezultat"] = "Odpowiedü serwera na komunikat Echo.";

		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Echo na serwerze.");
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Serwer: parametry_[\"Echo\"] = " + parametry_["Echo"].asString());
		}
	}

	bool EchoRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		auto value = odpowiedz["rezultat"];

		if (!parametry_["Echo"].empty()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Klient: parametry_[\"Echo\"] = " + parametry_["Echo"].asString());
			}
		}

		if (value.isString()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Komunikat Echo: " + value.asString());
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
