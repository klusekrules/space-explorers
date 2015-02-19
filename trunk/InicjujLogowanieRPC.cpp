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
		if (metoda.isNull()){
			// Tworzenie nowej pustej metody, do wys³ania na serwer
		} else{
			if ((*ptr) << metoda){
				//ptr->flagi_ = RPC_FLAG_AUTHORIZATION;
				// Uda³o siê odtworzyæ metodê, przypisanie parametrów wymaganych przez metodê do atrybutów metody.
			} else{
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod³a siê deserializacja metody InicjujLogowanieRPC.");
				return nullptr;
			}
		}
		return std::move(ptr);
	}

	void InicjujLogowanieRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Login");
		for (auto& p : parametry_){
			if (p.first == "Login"){
				auto hash = Aplikacja::pobierzInstancje().zarzadcaUzytkownikow_.pobierzHash(p.second);
				if (!hash.empty()){
					klient_.ustawKlucz(hash);
					flagi_ |= RPC_FLAG_AUTHORIZATION;
				}
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, p.second);
			}
		}
	}

	bool InicjujLogowanieRPC::inicjalizacjaParametrow(){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "InicjujLogowanieRPC::inicjalizacjaParametrow");
		parametry_.emplace_back("Login", login_);
		auto hash = Aplikacja::pobierzInstancje().zarzadcaUzytkownikow_.pobierzHash(login_);
		if (!hash.empty()){
			klient_.ustawKlucz(hash);
		}
		return true;
	}

	bool InicjujLogowanieRPC::obslugaOdpowiedzi(const Json::Value & odpowiedz){
		SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "InicjujLogowanieRPC::obslugaOdpowiedzi");
		
		return true;
	}

	std::string InicjujLogowanieRPC::napis() const {
		SLog::Logger log(NAZWAKLASY(InicjujLogowanieRPC));
		log.dodajKlase(MetodaRPC::napis());
		return std::move(log.napis());
	}

}
