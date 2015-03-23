#include "SprawdzSumyKontrolneRPC.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
#include "ZarzadcaZasobow.h"
#include "SumaKontrolnaPliku.h"
#include "Plugin.h"

namespace SpEx{

	const std::string SprawdzSumyKontrolneRPC::NazwaTypu_ = "SprawdzSumyKontrolne";
	
	std::string SprawdzSumyKontrolneRPC::napis() const{
		SLog::Logger logger(NAZWAKLASY(SprawdzSumyKontrolneRPC));
		logger.dodajKlase(MetodaRPC::napis());
		return logger.napis();
	}

	bool SprawdzSumyKontrolneRPC::inicjuj(){
		auto crcPlikGry = Aplikacja::pobierzInstancje().pobierzZarzadceZasobow().pobierzZasob<SumaKontrolnaPliku>(Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()["plikGry"]);
		if (crcPlikGry == nullptr)
			return false;
		return true;
	}

	void SprawdzSumyKontrolneRPC::obslugaZadania(const Json::Value &, Json::Value&){
	
	}

	bool SprawdzSumyKontrolneRPC::obslugaOdpowiedzi(const Json::Value &){
		return false;
	}
}
