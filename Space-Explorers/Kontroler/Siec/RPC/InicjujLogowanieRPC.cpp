#include "InicjujLogowanieRPC.h"
#include "StaleRPC.h"
#include "Parser\ParserDokumentXml.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Zarzadca\ZarzadcaUzytkownikow.h"
#include "Utils\Utils.h"
#include "Algorytmy\SHA3.h"

namespace SpEx{

	const std::string InicjujLogowanieRPC::NazwaTypu_ = "InicjujLogowanie";

	bool InicjujLogowanieRPC::przygotowanieDoWyslania(){
		auto jHash = parametry_["Hash"];		
		if (jHash != Json::nullValue){
			auto hash = jHash.asString();
			parametry_.removeMember("Hash");
			if (!hash.empty()){
				klient_.ustawKlucz(hash);
				return true;
			}
		}
		return false;
	}

	void InicjujLogowanieRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Login");
		}
		auto login = parametry_["Login"];
		if (login != Json::nullValue){
			auto hash = Aplikacja::pobierzInstancje().pobierzZarzadceUzytkownikow().pobierzHash(login.asString());
			if (!hash.empty()){
				klient_.ustawKlucz(hash);
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Inicjalizacja logowania u¿ytkownika " + login.asString() + " dla ip " + klient_.pobierzIP());
				}
			} else{
				SHA3 fakeSha(std::to_string(Utils::pobierzLiczbeLosowa()));
				std::string fakehash(std::move(fakeSha.pobierzNapis()));
				klient_.ustawKlucz(fakehash);
				if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Brak u¿ytkownika o podanym loginie: " + login.asString() + " dla ip " + klient_.pobierzIP());
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Fake hash: " + fakehash);
				}
			}

			auto liczba = Utils::pobierzLiczbeLosowa();
			klient_.ustawAutoryzacje(Utils::konwertujDoHex((const char *)&(liczba), sizeof(__int64), true));
			liczba = Utils::pobierzLiczbeLosowa();
			klient_.ustawInstancje(Utils::konwertujDoHex((const char *)&(liczba), sizeof(__int64), true));
			klient_.autoryzujMetode(instancja_, autoryzacja_);
			odpowiedz[METODA_RPC_AUTORYZACJA] = autoryzacja_;
			odpowiedz[METODA_RPC_INSTANCJA] = instancja_;
			flagi_ |= RPC_FLAG_AUTHORIZATION;
		}		
	}
	
	bool InicjujLogowanieRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Debug)){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "InicjujLogowanieRPC::obslugaOdpowiedzi");
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Odebrano - autoryzacja: " + odpowiedz[METODA_RPC_AUTORYZACJA].asString());
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Debug, "Odebrano - instancja: " + odpowiedz[METODA_RPC_INSTANCJA].asString());
		}
		klient_.ustawAutoryzacje(odpowiedz[METODA_RPC_AUTORYZACJA].asString());
		klient_.ustawInstancje(odpowiedz[METODA_RPC_INSTANCJA].asString());
		return true;
	}

	std::string InicjujLogowanieRPC::napis() const {
		SLog::Logger log(NAZWAKLASY(InicjujLogowanieRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}

}
