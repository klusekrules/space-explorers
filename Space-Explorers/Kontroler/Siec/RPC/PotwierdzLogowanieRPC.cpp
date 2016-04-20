#include "PotwierdzLogowanieRPC.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"

namespace SpEx{

	const std::string PotwierdzLogowanieRPC::NazwaTypu_ = "PotwierdzLogowanie";
	
	void PotwierdzLogowanieRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		std::string autoryzacja, instancja;
		klient_.autoryzujMetode(instancja, autoryzacja);
		if (autoryzacja_ == autoryzacja && instancja_ == instancja){
			odpowiedz[METODA_RPC_RETURN] = true;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Udane logowanie u¿ytkownika (nn) dla ip " + klient_.pobierzAdres());
			}
		} else{
			odpowiedz[METODA_RPC_RETURN] = false;
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, "Nie udana próba logowania u¿ytkownika (nn) dla ip " + klient_.pobierzAdres());
			}
		}
	}
	
	bool PotwierdzLogowanieRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz) {
		if (odpowiedz[METODA_RPC_RETURN].isBool()){
			return odpowiedz[METODA_RPC_RETURN].asBool();
		}
		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie udane logowanie. B³êdne dane.");
		}
		return false;
	}

	std::string PotwierdzLogowanieRPC::napis() const {
		SLog::Logger log(NAZWAKLASY(PotwierdzLogowanieRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}
}