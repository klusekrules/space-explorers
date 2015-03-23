#include "SprawdzSumyKontrolneRPC.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
#include "ZarzadcaZasobow.h"
#include "SumaKontrolnaPliku.h"
#include "Plugin.h"
#include "StaleRPC.h"
#include "StaleUstawienAplikacji.h"

namespace SpEx{

	static inline std::string& pobierzAdresPliku(const std::string nazwa){
		return Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()[nazwa];
	}

	static inline SumaKontrolnaPliku::SharedPtr pobierzSumeKontrolna(const std::string& adres){
		return Aplikacja::pobierzInstancje().pobierzZarzadceZasobow().pobierzZasob<SumaKontrolnaPliku>(adres);
	}

	const std::string SprawdzSumyKontrolneRPC::NazwaTypu_ = "SprawdzSumyKontrolne";
	
	std::string SprawdzSumyKontrolneRPC::napis() const{
		SLog::Logger logger(NAZWAKLASY(SprawdzSumyKontrolneRPC));
		logger.dodajKlase(MetodaRPC::napis());
		return logger.napis();
	}

	bool SprawdzSumyKontrolneRPC::przygotowanieDoWyslania(){
		auto crcPlikGry = pobierzSumeKontrolna(pobierzAdresPliku(ATRYBUT_PLIK_DANYCH));
		if (crcPlikGry == nullptr || crcPlikGry->pobierzSumeKontrolna().pobierzKontener().empty())
			return false;
		parametry_[ATRYBUT_PLIK_DANYCH] = crcPlikGry->pobierzSumeKontrolna().pobierzNapis();
		return true;
	}

	void SprawdzSumyKontrolneRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		auto klientCrcPlikGry = zadanie[METODA_RPC_METODA][METODA_RPC_PARAMETRY][ATRYBUT_PLIK_DANYCH].asString();
		auto crcPlikGry = pobierzSumeKontrolna(pobierzAdresPliku(ATRYBUT_PLIK_DANYCH));
		if (crcPlikGry != nullptr && klientCrcPlikGry == crcPlikGry->pobierzSumeKontrolna().pobierzNapis()){
			odpowiedz[ATRYBUT_PLIK_DANYCH] = true;
		} else{
			odpowiedz[ATRYBUT_PLIK_DANYCH] = false;
		}
	}

	bool SprawdzSumyKontrolneRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		if (!odpowiedz[ATRYBUT_PLIK_DANYCH].asBool())
			return false;
		return true;
	}
}
