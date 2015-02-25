#include "EchoRPC.h"
#include "Fabrykator.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"

namespace SpEx{

	bool EchoRPC::RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger){
		return fabryka.rejestracjaMetodyRPC(STyp::Tekst("Echo"), EchoRPC::TworzObiekt);
	}

	std::shared_ptr<MetodaRPC> EchoRPC::TworzObiekt(const Json::Value & metoda, Klient& klient){
		auto ptr = std::make_shared<EchoRPC>(klient);
		if (!metoda.isNull() && !((*ptr) << metoda)){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod³a siê deserializacja metody Echo.");
			}
			return nullptr;
		}
		return std::move(ptr);
	}

	EchoRPC::EchoRPC(Klient& polaczenie)
		: MetodaRPC(polaczenie)
	{
	}

	void EchoRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		parametry_["Echo"] = "Do klienta";
		odpowiedz["rezultat"] = "OdpowiedŸ serwera na komunikat Echo.";

		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Echo na serwerze.");
		}
	}

	bool EchoRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		auto value = odpowiedz["rezultat"];

		if (!parametry_["Echo"].empty()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, parametry_["Echo"]);
			}
		}

		if (value.isString()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Komunikat Echo: " + value.asString());
			}
			return true;
		}else{
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Niepoprawna odpowiedŸ na komunikat Echo.");
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
