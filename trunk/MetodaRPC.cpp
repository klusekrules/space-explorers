#include "MetodaRPC.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "NiezaimplementowanaMetoda.h"

#define BRAK_ELEMENTU(n) "MetodaRPC::odczytajWezel -> " + std::string(n)
#define METODA_RPC_ID "id"
#define METODA_RPC_NAZWA "nazwa"
#define METODA_RPC_ID_UNIKALNE "id-unikalne"
#define METODA_RPC_POWTORZENIE "powtorzenie"
#define METODA_RPC_CZAS_WYWOLANIA "czas-wywolania"
#define METODA_RPC_CZAS_ODPOWIEDZI "czas-odpowiedzi"
#define METODA_RPC_PARAMETRY "parametry"

namespace SpEx{

	MetodaRPC::MetodaRPC(const PolaczenieTCP& polaczenie)
		: polaczenie_(polaczenie)
	{}

	bool MetodaRPC::operator<< (const Json::Value & root){
		auto &v_Id = root[METODA_RPC_ID];
		if (!v_Id){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_ID));
			return false;
		}

		auto &v_Nazwa = root[METODA_RPC_NAZWA];
		if (!v_Nazwa){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_NAZWA));
			return false;
		}

		auto &v_Id_Unikalne = root[METODA_RPC_ID_UNIKALNE];
		if (!v_Id_Unikalne){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_ID_UNIKALNE));
			return false;
		}

		auto &v_Powtorzenie = root[METODA_RPC_POWTORZENIE];
		if (!v_Powtorzenie){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_POWTORZENIE));
			return false;
		}

		auto &v_Czas_Wywolania = root[METODA_RPC_CZAS_WYWOLANIA];
		if (!v_Czas_Wywolania){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_CZAS_WYWOLANIA));
			return false;
		}

		auto &v_Czas_Odpowiedzi = root[METODA_RPC_CZAS_ODPOWIEDZI];
		if (!v_Czas_Odpowiedzi){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_CZAS_ODPOWIEDZI));
			return false;
		}

		id_ = v_Id.asString();
		nazwa_ = v_Nazwa.asString();
		id_unikalne_ = v_Id_Unikalne.asString();
		powtorzenie_ = v_Powtorzenie.asUInt();
		czas_wywolania_ = v_Czas_Wywolania.asString();
		czas_odpowiedzi_ = v_Czas_Odpowiedzi.asString();
		auto & v_parametry = root[METODA_RPC_PARAMETRY];
		for (auto& val : v_parametry.getMemberNames()){
			parametry_.emplace_back(val, v_parametry[val].asString());
		}

		return true;
	}

	void MetodaRPC::operator()(const Json::Value &, Json::Value&){
		throw NiezaimplementowanaMetoda(EXCEPTION_PLACE);
	}

	bool MetodaRPC::operator()(){
		try{
			if (inicjalizacjaParametrow()){
				Json::Value procedura;
				(*this) >> procedura;
				Json::FastWriter writer;
				auto zadanie = std::make_shared<const std::string>(writer.write(procedura));
				auto wiadomoscZwrotna = std::make_shared<std::string>();
				if (polaczenie_.wyslij(zadanie, wiadomoscZwrotna)){
					Json::Reader reader;
					Json::Value result;
					if (reader.parse(*wiadomoscZwrotna, result)){
						return obslugaOdpowiedzi(result);
					}else{
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error,"Nieuda³o siê zintepretowaæ wiadomoœci zwrotnej: " + *wiadomoscZwrotna);
						SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, (*this));
					}
				}else{
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Wyst¹pi³ b³¹d przy próbie wys³ania ¿adania: " + *zadanie);
					SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, (*this));
				}
			}else{
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Wyst¹pi³ b³¹d podczas inicjalizacji parametrów.");
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, (*this));
			}
		}
		catch (NiezaimplementowanaMetoda& e){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Wyst¹pi³ wyj¹tek podczas wykonywania metody RPC.");
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, e.generujKomunikat());
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, (*this));
		}
		return false;
	}

	bool MetodaRPC::inicjalizacjaParametrow(){
		throw NiezaimplementowanaMetoda(EXCEPTION_PLACE);
	}

	bool MetodaRPC::obslugaOdpowiedzi(const Json::Value &){
		throw NiezaimplementowanaMetoda(EXCEPTION_PLACE);
	}
	
	const MetodaRPC& MetodaRPC::operator>>(Json::Value &root) const{
		root[METODA_RPC_ID] = id_;
		root[METODA_RPC_NAZWA] = nazwa_;
		root[METODA_RPC_ID_UNIKALNE] = id_unikalne_;
		root[METODA_RPC_POWTORZENIE] = powtorzenie_;
		root[METODA_RPC_CZAS_WYWOLANIA] = czas_wywolania_;
		root[METODA_RPC_CZAS_ODPOWIEDZI] = czas_odpowiedzi_;
		for (auto& p : parametry_){
			root[METODA_RPC_PARAMETRY][p.first] = p.second;
		}
		return *this;
	}

	std::string MetodaRPC::napis() const{
		SLog::Logger log(NAZWAKLASY(MetodaRPC));
		log.dodajPole(NAZWAPOLA(id_), "std::string", id_);
		log.dodajPole(NAZWAPOLA(nazwa_), "std::string", nazwa_);
		log.dodajPole(NAZWAPOLA(id_unikalne_), "std::string", id_unikalne_);
		log.dodajPole(NAZWAPOLA(czas_wywolania_), "std::string", czas_wywolania_);
		log.dodajPole(NAZWAPOLA(czas_odpowiedzi_), "std::string", czas_odpowiedzi_);
		log.dodajPole(NAZWAPOLA(powtorzenie_), NAZWAKLASY2(powtorzenie_), std::to_string(powtorzenie_));

		log.rozpocznijPodKlase(NAZWAPOLA(parametry_), "std::vector <Parametr>");
		for (auto e : parametry_){
			log.rozpocznijPodKlase("para", "Parametr");
			log.dodajPole("first", "std::string", e.first);
			log.dodajPole("second", "std::string", e.second);
			log.zakonczPodKlase();
		}
		log.zakonczPodKlase();

		log.dodajPole(NAZWAPOLA(polaczenie_), polaczenie_);
		return log.napis();
	}
}
