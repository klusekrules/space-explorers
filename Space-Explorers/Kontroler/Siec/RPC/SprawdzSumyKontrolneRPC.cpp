#include "SprawdzSumyKontrolneRPC.h"
#include "Logger\Logger.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Zarzadca\ZarzadcaZasobow.h"
#include "Kontroler\Zarzadca\SumaKontrolnaPliku.h"
#include "Kontroler\Zarzadca\ZarzadcaPluginow.h"
#include "StaleRPC.h"
#include "Utils\StaleUstawienAplikacji.h"

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
		if (crcPlikGry == nullptr || crcPlikGry->pobierzSumeKontrolna().pobierzKontener().empty()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak sumy kontrolnej pliku z danymi.");
			}
			return false;
		}
		parametry_[ATRYBUT_PLIK_DANYCH] = std::move(crcPlikGry->pobierzSumeKontrolna().pobierzNapis());
		auto& lista = Aplikacja::pobierzInstancje().pobierzZarzadcePluginow().pobierzListeSumKontrolnych();
		for (auto& ptr : lista){
			if (ptr != nullptr){
				parametry_[ptr->pobierzAdresPliku()] = std::move(ptr->pobierzSumeKontrolna().pobierzNapis());
			} else{
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie poprawny zasob sumy kontrolnej.");
				}
				return false;
			}
		}
		return true;
	}

	void SprawdzSumyKontrolneRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		auto crcPlikGry = pobierzSumeKontrolna(pobierzAdresPliku(ATRYBUT_PLIK_DANYCH));
		if (parametry_[ATRYBUT_PLIK_DANYCH].isString() && crcPlikGry != nullptr){
			auto sumaKontrolnaKlient = std::move(parametry_[ATRYBUT_PLIK_DANYCH].asString());
			auto sumaKontrolnaSerwer = std::move(crcPlikGry->pobierzSumeKontrolna().pobierzNapis());				
			odpowiedz[ATRYBUT_PLIK_DANYCH] = !sumaKontrolnaKlient.empty() && !sumaKontrolnaSerwer.empty() && sumaKontrolnaKlient == sumaKontrolnaSerwer;
		} else{
			odpowiedz[ATRYBUT_PLIK_DANYCH] = false;
		}

		auto& lista = Aplikacja::pobierzInstancje().pobierzZarzadcePluginow().pobierzListeSumKontrolnych();
		for (auto& ptr : lista){
			if (ptr != nullptr){
				auto& suma = parametry_[ptr->pobierzAdresPliku()];
				if (suma.isString()){
					auto sumaKontrolnaKlient = std::move(suma.asString());
					auto sumaKontrolnaSerwer = std::move(ptr->pobierzSumeKontrolna().pobierzNapis());
					odpowiedz[ptr->pobierzAdresPliku()] = !sumaKontrolnaKlient.empty() && !sumaKontrolnaSerwer.empty() && sumaKontrolnaKlient == sumaKontrolnaSerwer;
				} else{
					parametry_.removeMember(ptr->pobierzAdresPliku());
					odpowiedz[ptr->pobierzAdresPliku()] = false;
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak sumy kontrolnej pliku :" + ptr->pobierzAdresPliku());
					}
				}
			} else{
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie poprawny zasob sumy kontrolnej.");
				}
			}
		}

	}

	bool SprawdzSumyKontrolneRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		bool ok = true;
		for (auto& member : odpowiedz.getMemberNames()){
			if (odpowiedz[member].isBool()){
				if (odpowiedz[member].asBool()){
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, member + " - plik poprawny");
					}
				} else{
					if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Warning)){
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Warning, member + " - plik nie poprawny");
					}
					ok = false;
				}
			}
		}		
		return ok;
	}
}
