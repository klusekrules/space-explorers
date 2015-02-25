#include "InicjujLogowanieRPC.h"
#include "Fabrykator.h"
#include "StaleRPC.h"
#include "Parser\ParserDokumentXml.h"
#include "Aplikacja.h"

namespace SpEx{

	InicjujLogowanieRPC::InicjujLogowanieRPC(Klient& polaczenie)
		: MetodaRPC(polaczenie)
	{
	}

	bool InicjujLogowanieRPC::RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger){
		return fabryka.rejestracjaMetodyRPC(STyp::Tekst("InicjujLogowanie"), InicjujLogowanieRPC::TworzObiekt);
	}

	std::shared_ptr<MetodaRPC> InicjujLogowanieRPC::TworzObiekt(const Json::Value& metoda, Klient& klient){
		auto ptr = std::make_shared<InicjujLogowanieRPC>(klient);
		if (!metoda.isNull() && !((*ptr) << metoda)){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod³a siê deserializacja metody InicjujLogowanieRPC.");
			}
			return nullptr;
		}
		return std::move(ptr);
	}
	
	bool InicjujLogowanieRPC::przygotowanieDoWyslania(){
		auto iter = parametry_.find("Hash");		
		if (iter!=parametry_.end()){
			auto hash = iter->second;
			parametry_.erase(iter);
			if (!hash.empty()){
				klient_.ustawKlucz(hash);
				return true;
			}
		}
		return false;
	}

	void InicjujLogowanieRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Login");
		auto iter = parametry_.find("Login");
		if (iter!=parametry_.end()){
			auto hash = Aplikacja::pobierzInstancje().zarzadcaUzytkownikow_.pobierzHash(iter->second);
			if (!hash.empty()){
				klient_.ustawKlucz(hash);
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
	}
	
	bool InicjujLogowanieRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Info)){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "InicjujLogowanieRPC::obslugaOdpowiedzi");
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Odebrano - autoryzacja: " + odpowiedz[METODA_RPC_AUTORYZACJA].asString());
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Odebrano - instancja: " + odpowiedz[METODA_RPC_INSTANCJA].asString());
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
