#include <io.h>
#include "PobierzPlikRPC.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"
#include "..\RAW\SerwerRaw.h"
#include "..\RAW\KlientRaw.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Wielowatkowosc\ObserwatorWatkow.h"
#include "Narzedzia\Stale.h"
#include "Utils\Utils.h"

namespace SpEx {

	const std::string PobierzPlikRPC::NazwaTypu_ = "PobierzPlikRPC";

	void PobierzPlikRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz) {
		auto nazwaPliku = parametry_["Plik"];
		FILE *fp = nullptr;
		if (!nazwaPliku.isString() || nazwaPliku.asString().empty()) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku do wys³ania.");
			ustawBlad(1, "Brak pliku do wys³ania.");
			odpowiedz[METODA_RPC_RETURN] = false;
		}else {
			auto nazwaPlikuDanych_ = Utils::adresPliku(nazwaPliku.asString());
			if (!nazwaPlikuDanych_.empty()) {
				if (_access(nazwaPlikuDanych_.c_str(), 0) == -1) {
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak pliku do wys³ania.");
					ustawBlad(2, "Brak pliku do wys³ania.");
					odpowiedz[METODA_RPC_RETURN] = false;
					return;
				}
				fp = fopen(nazwaPlikuDanych_.c_str(), "rb");
				if (fp == nullptr) {
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie uda³o siê otworzyæ pliku do wys³ania. Numer b³êdu: " + std::to_string(errno));
					ustawBlad(3, "Nie uda³o siê otworzyæ pliku do wys³ania. Numer b³êdu: " + std::to_string(errno));
					odpowiedz[METODA_RPC_RETURN] = false;		
					return;
				}
			}else{
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie ma pliku o podanej nazwie.");
				ustawBlad(4, "Nie ma pliku o podanej nazwie.");
				odpowiedz[METODA_RPC_RETURN] = false;
				return;
			}
			auto ptr = ObserwatorWatkow::make_thread<SerwerRaw>(nazwaPlikuDanych_, fp);
			odpowiedz["NazwaPliku"] = nazwaPlikuDanych_;
			odpowiedz["Port"] = ptr->pobierzPort();
			ptr->odblokuj();
			odpowiedz[METODA_RPC_RETURN] = true;
		}
	}

	bool PobierzPlikRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz) {
		auto retVal = odpowiedz[METODA_RPC_RETURN];
		if (!retVal.isBool() || !retVal.asBool()) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d numer: " + std::to_string(numerBledu_) + " Treœæ: " + komuniaktBledu_);
			return false;
		}
		std::string adresPliku = Utils::adresPliku(parametry_["Plik"].asString());

		FILE* fp = fopen(adresPliku.c_str(),"wb");
		auto plik = ObserwatorWatkow::make_thread<KlientRaw>(odpowiedz["NazwaPliku"].asString(),fp,std::string("127.0.0.1"), odpowiedz["Port"].asInt());
		plik->odblokuj();
		plik->czekajNaZakonczenie();
		int kod = plik->kodPowrotu();
		if (kod != ERROR_SUCCESS) {
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d " + std::to_string(kod) +" podczas pobierania pliku: " + adresPliku);
			return false;
		}
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Pobrano plik: " + adresPliku);
		return true;
	}

	std::string PobierzPlikRPC::napis() const {
		SLog::Logger log(NAZWAKLASY(PobierzPlikRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}

}
