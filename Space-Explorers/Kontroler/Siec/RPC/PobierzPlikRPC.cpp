#include <io.h>
#include "PobierzPlikRPC.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"
#include "..\RAW\SerwerRaw.h"
#include "..\RAW\KlientRaw.h"
#include "Kontroler\Aplikacja.h"

namespace SpEx {

	const std::string PobierzPlikRPC::NazwaTypu_ = "PobierzPlikRPC";

	void PobierzPlikRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz) {
		auto nazwaPliku = parametry_["Plik"];
		FILE *fp = nullptr;
		if (!nazwaPliku.isString() || nazwaPliku.asString().empty()) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku do wys³ania.");
			odpowiedz[METODA_RPC_RETURN] = false;
		}
		else {
			auto nazwaPlikuDanych_ = Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji()[nazwaPliku.asString()];
			if (!nazwaPlikuDanych_.empty()) {
				if (_access(nazwaPlikuDanych_.c_str(), 0) == -1) {
					odpowiedz[METODA_RPC_RETURN] = false;
					return;
				}
				fp = fopen(nazwaPlikuDanych_.c_str(), "rb");
				if (fp == nullptr) {
					odpowiedz[METODA_RPC_RETURN] = false;		
					return;
				}
			}else{
				odpowiedz[METODA_RPC_RETURN] = false;
				return;
			}
			auto ptr = new SerwerRaw(nazwaPlikuDanych_, fp);
			odpowiedz["NazwaPliku"] = nazwaPlikuDanych_;
			odpowiedz["Port"] = ptr->pobierzPort();
			ptr->odblokuj();
			odpowiedz[METODA_RPC_RETURN] = true;
		}
	}

	bool PobierzPlikRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz) {
		auto retVal = odpowiedz[METODA_RPC_RETURN];
		if (!retVal.isBool() || !retVal.asBool()) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d");
			return false;
		}
		FILE* fp = fopen("daneTestMetody.xml","wb");
		KlientRaw plik(odpowiedz["NazwaPliku"].asString(),fp,"127.0.0.1", odpowiedz["Port"].asInt());
		plik.odblokuj();
		plik.czekajNaZakonczenie();
		int kod = plik.kodPowrotu();		
		if (kod != ERROR_SUCCESS) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d pobierania pliku: " + std::to_string(kod));
			return false;
		}		
		return true;
	}

	std::string PobierzPlikRPC::napis() const {
		SLog::Logger log(NAZWAKLASY(PobierzPlikRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}

}
