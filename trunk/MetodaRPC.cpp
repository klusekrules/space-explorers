#include "MetodaRPC.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "NiezaimplementowanaMetoda.h"
#include "CRC64.h"
#include "StaleRPC.h"

#define BRAK_ELEMENTU(n) "MetodaRPC::odczytajWezel -> " + std::string(n)

namespace SpEx{

	MetodaRPC::MetodaRPC(const PolaczenieTCP& polaczenie)
		: polaczenie_(polaczenie)
	{}

	bool MetodaRPC::operator<< (const Json::Value & root){
		auto &v_Autoryzacja = root[METODA_RPC_AUTORYZACJA];
		if (!v_Autoryzacja){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_AUTORYZACJA));
			return false;
		}

		auto &v_Instancja = root[METODA_RPC_INSTANCJA];
		if (!v_Instancja){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_INSTANCJA));
			return false;
		}

		auto metoda = root[METODA_RPC_METODA];
		if (!metoda.isObject()){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_METODA));
			return false;
		}

		auto &v_Nazwa = metoda[METODA_RPC_NAZWA];
		if (!v_Nazwa){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_NAZWA));
			return false;
		}

		auto &v_Id_Unikalne = metoda[METODA_RPC_ID_UNIKALNE];
		if (!v_Id_Unikalne){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_ID_UNIKALNE));
			return false;
		}

		auto &v_Powtorzenie = metoda[METODA_RPC_POWTORZENIE];
		if (!v_Powtorzenie){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_POWTORZENIE));
			return false;
		}

		auto &v_Czas_Wywolania = metoda[METODA_RPC_CZAS_WYWOLANIA];
		if (!v_Czas_Wywolania){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_CZAS_WYWOLANIA));
			return false;
		}

		auto &v_Czas_Odpowiedzi = metoda[METODA_RPC_CZAS_ODPOWIEDZI];
		if (!v_Czas_Odpowiedzi){
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_CZAS_ODPOWIEDZI));
			return false;
		}

		autoryzacja_ = v_Autoryzacja.asString();
		instancja_ = v_Instancja.asString();
		nazwa_ = v_Nazwa.asString();
		id_unikalne_ = v_Id_Unikalne.asString();
		powtorzenie_ = v_Powtorzenie.asUInt();
		czas_wywolania_ = v_Czas_Wywolania.asString();
		czas_odpowiedzi_ = v_Czas_Odpowiedzi.asString();
		auto & v_parametry = metoda[METODA_RPC_PARAMETRY];
		for (auto& val : v_parametry.getMemberNames()){
			parametry_.emplace_back(val, v_parametry[val].asString());
		}

		return true;
	}

	void MetodaRPC::obslugaZadania(const Json::Value &, Json::Value&){
		throw NiezaimplementowanaMetoda(EXCEPTION_PLACE);
	}


	void MetodaRPC::dodajCRC(Json::Value& procedura){
		procedura["CRC"] = "";
		Json::FastWriter writer;
		auto jsZadanie = writer.write(procedura);
		procedura["CRC"] = CRC64().calc(jsZadanie.c_str(), jsZadanie.size());
	}
	
	bool MetodaRPC::sprawdzCRC(Json::Value& result){
		Json::FastWriter writer;
		auto crc = result["CRC"].asUInt64();
		result["CRC"] = "";
		auto toCheck = writer.write(result);
		auto newCRC = CRC64().calc(toCheck.c_str(), toCheck.size());
		if (newCRC == crc){
			return true;
		} else{
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, std::to_string(crc));
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, std::to_string(newCRC));
			return false;
		}
	}

	bool MetodaRPC::operator()(){
		try{
			if (inicjalizacjaParametrow()){
				Json::Value procedura;
				(*this) >> procedura;
				Json::FastWriter writer;
				dodajCRC(procedura);
				auto zadanie = std::make_shared<const std::string>(writer.write(procedura));
				auto wiadomoscZwrotna = std::make_shared<std::string>();
				if (polaczenie_.wyslij(zadanie, wiadomoscZwrotna)){
					Json::Reader reader;
					Json::Value result;
					if (reader.parse(*wiadomoscZwrotna, result)){
						if (sprawdzCRC(result)){
							//Sprawdzenie czy zosta³ wyrzucony wyj¹tek;
							if (!result[METODA_RPC_THROW].isNull()){
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Otrzymano wyj¹tek: typ: " + result[METODA_RPC_THROW][METODA_RPC_TYPE].asString() + " komunikat:  " + result[METODA_RPC_THROW][METODA_RPC_KOMUNIKAT].asString());
								SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, (*this));
							} else{
								return obslugaOdpowiedzi(result);
							}
						} else{
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "Niepoprawne dane. B³¹d sumy kontrolnej. Wiadomoœæ: " + *wiadomoscZwrotna);
							SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, (*this));
						}
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
		root[METODA_RPC_AUTORYZACJA] = autoryzacja_;
		root[METODA_RPC_INSTANCJA] = instancja_;

		root[METODA_RPC_METODA] = Json::Value(Json::objectValue);
		auto& metoda = root[METODA_RPC_METODA];
		metoda[METODA_RPC_NAZWA] = nazwa_;
		metoda[METODA_RPC_ID_UNIKALNE] = id_unikalne_;
		metoda[METODA_RPC_POWTORZENIE] = powtorzenie_;
		metoda[METODA_RPC_CZAS_WYWOLANIA] = czas_wywolania_;
		metoda[METODA_RPC_CZAS_ODPOWIEDZI] = czas_odpowiedzi_;
		for (auto& p : parametry_){
			metoda[METODA_RPC_PARAMETRY][p.first] = p.second;
		}
		return *this;
	}

	std::string MetodaRPC::napis() const{
		SLog::Logger log(NAZWAKLASY(MetodaRPC));
		log.dodajPole(NAZWAPOLA(autoryzacja_), "std::string", autoryzacja_);
		log.dodajPole(NAZWAPOLA(instancja_), "std::string", instancja_);
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
