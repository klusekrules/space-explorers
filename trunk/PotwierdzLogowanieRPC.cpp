#include "PotwierdzLogowanieRPC.h"
#include "Fabrykator.h"
#include "Logger\Logger.h"
#include "StaleRPC.h"

#define METODA_RPC_RESULT "result"

namespace SpEx{
	PotwierdzLogowanieRPC::PotwierdzLogowanieRPC(Klient& gniazdo)
		: MetodaRPC(gniazdo)
	{
	}

	bool PotwierdzLogowanieRPC::RejestratorMetodyRPC(Fabrykator& fabryka, SLog::Log& logger){
		return fabryka.rejestracjaMetodyRPC(STyp::Tekst("PotwierdzLogowanie"), PotwierdzLogowanieRPC::TworzObiekt);
	}

	std::shared_ptr<MetodaRPC> PotwierdzLogowanieRPC::TworzObiekt(const Json::Value & metoda, Klient& klient){
		auto ptr = std::make_shared<PotwierdzLogowanieRPC>(klient);
		if (metoda.isNull()){
			// Tworzenie nowej pustej metody, do wys³ania na serwer
		} else{
			if ((*ptr) << metoda){
				// Uda³o siê odtworzyæ metodê, przypisanie parametrów wymaganych przez metodê do atrybutów metody.
			} else{
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Nie powiod³a siê deserializacja metody ZalogujRPC.");
				return nullptr;
			}
		}
		return std::move(ptr);
	}
	
	void PotwierdzLogowanieRPC::obslugaZadania(const Json::Value & zadanie, Json::Value& odpowiedz){
		std::string autoryzacja, instancja;
		klient_.autoryzujMetode(instancja, autoryzacja);
		if (autoryzacja_ == autoryzacja && instancja_ == instancja){
			odpowiedz[METODA_RPC_RESULT] = true;
		} else{
			odpowiedz[METODA_RPC_RESULT] = false;		
		}
		//TODO: Inicjalizacja wczytywania gracza.
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