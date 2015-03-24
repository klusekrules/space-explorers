#include "PotwierdzLogowanieRPC.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"

#define METODA_RPC_RESULT "result"

namespace SpEx{

	const std::string PotwierdzLogowanieRPC::NazwaTypu_ = "PotwierdzLogowanie";
	
	void PotwierdzLogowanieRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		std::string autoryzacja, instancja;
		klient_.autoryzujMetode(instancja, autoryzacja);
		if (autoryzacja_ == autoryzacja && instancja_ == instancja){
			odpowiedz[METODA_RPC_RESULT] = true;
		} else{
			odpowiedz[METODA_RPC_RESULT] = false;		
		}
	}
	
	bool PotwierdzLogowanieRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz) {
		if (odpowiedz[METODA_RPC_RESULT].isBool()){
			return odpowiedz[METODA_RPC_RESULT].asBool();
		}
		return false;
	}

	std::string PotwierdzLogowanieRPC::napis() const {
		SLog::Logger log(NAZWAKLASY(PotwierdzLogowanieRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}
}