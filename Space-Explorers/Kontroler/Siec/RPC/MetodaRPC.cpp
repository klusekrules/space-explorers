#include "MetodaRPC.h"
#include "Logger\Log.h"
#include "Logger\Logger.h"
#include "Wyjatki\NiezaimplementowanaMetoda.h"
#include "Algorytmy\CRC64.h"
#include "StaleRPC.h"

#define BRAK_ELEMENTU(n) "MetodaRPC::odczytajWezel -> " + std::string(n)

namespace SpEx{

	MetodaRPC::MetodaRPC(KlientSideMulti& klient)
		: klient_(klient), flagi_(0)
	{}

	bool MetodaRPC::inicjuj(){
		return true;
	}

	bool MetodaRPC::inicjuj(const Json::Value&){
		return true;
	}

	bool MetodaRPC::operator<< (const Json::Value & root){
		auto &v_Autoryzacja = root[METODA_RPC_AUTORYZACJA];
		if (!v_Autoryzacja){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_AUTORYZACJA));
			}
			return false;
		}

		auto &v_Instancja = root[METODA_RPC_INSTANCJA];
		if (!v_Instancja){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_INSTANCJA));
			}
			return false;
		}

		auto metoda = root[METODA_RPC_METODA];
		if (!metoda.isObject()){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_METODA));
			}
			return false;
		}

		auto &v_Nazwa = metoda[METODA_RPC_NAZWA];
		if (!v_Nazwa){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_NAZWA));
			}
			return false;
		}

		auto &v_Id_Unikalne = metoda[METODA_RPC_ID_UNIKALNE];
		if (!v_Id_Unikalne){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_ID_UNIKALNE));
			}
			return false;
		}

		auto &v_Powtorzenie = metoda[METODA_RPC_POWTORZENIE];
		if (!v_Powtorzenie){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_POWTORZENIE));
			}
			return false;
		}

		auto &v_Czas_Wywolania = metoda[METODA_RPC_CZAS_WYWOLANIA];
		if (!v_Czas_Wywolania){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_CZAS_WYWOLANIA));
			}
			return false;
		}

		auto &v_Czas_Odpowiedzi = metoda[METODA_RPC_CZAS_ODPOWIEDZI];
		if (!v_Czas_Odpowiedzi){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, BRAK_ELEMENTU(METODA_RPC_CZAS_ODPOWIEDZI));
			}
			return false;
		}

		autoryzacja_ = v_Autoryzacja.asString();
		instancja_ = v_Instancja.asString();
		nazwa_ = v_Nazwa.asString();
		id_unikalne_ = v_Id_Unikalne.asString();
		powtorzenie_ = v_Powtorzenie.asUInt();
		czas_wywolania_ = v_Czas_Wywolania.asString();
		czas_odpowiedzi_ = v_Czas_Odpowiedzi.asString();
		parametry_ = metoda[METODA_RPC_PARAMETRY];
		return true;
	}

	void MetodaRPC::obslugaZadania(const Json::Value &, Json::Value&){
		throw NiezaimplementowanaMetoda(EXCEPTION_PLACE);
	}

	int MetodaRPC::pobierzFlagi() const{
		return flagi_;
	}

	void MetodaRPC::dodajCRC(Json::Value& procedura){
		procedura[METODA_RPC_CRC] = 0;
		Json::FastWriter writer;
		auto jsZadanie = writer.write(procedura);
		procedura[METODA_RPC_CRC] = CRC64().calc(jsZadanie.c_str(), jsZadanie.size());
	}

	int MetodaRPC::sprawdzCRC(Json::Value& result){
		Json::FastWriter writer;
		if (!result[METODA_RPC_CRC].isUInt64()){
			return RPC_ERROR_MISSING_CRC;
		}
		auto crc = result[METODA_RPC_CRC].asUInt64();
		result[METODA_RPC_CRC] = 0;
		auto toCheck = writer.write(result);
		auto newCRC = CRC64().calc(toCheck.c_str(), toCheck.size());
		if (newCRC == crc){
			return RPC_OK;
		} else{
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, std::string("Podane crc: ") + std::to_string(crc));
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, std::string("Wyliczone crc: ") + std::to_string(newCRC));
			}
			return RPC_ERROR_INVALID_CRC;
		}
	}

	int MetodaRPC::waliduj(Json::Value& result, bool odpowiedz){
		int error = sprawdzCRC(result);
		if (error){
			return error;
		}
		if (error = sprawdzMetode(result, odpowiedz)){
			return error;
		}
		if ((error = sprawdzAutoryzacje(result)) == RPC_ERROR_WITHOUT_AUTHORIZED){
			error = sprawdzMetodeUprzywilejowana(result);
		}
		return error;
	}

	int MetodaRPC::sprawdzMetode(const Json::Value& root, bool odpowiedz){
		if (!root[METODA_RPC_AUTORYZACJA].isString())
			return RPC_ERROR_MISSING_AUTORYZACJA;

		if (!root[METODA_RPC_INSTANCJA].isString())
			return RPC_ERROR_MISSING_INSTANCJA;

		const Json::Value& metoda = root[METODA_RPC_METODA];

		if (!metoda.isObject())
			return RPC_ERROR_MISSING_METODA;

		if (!metoda[METODA_RPC_NAZWA].isString())
			return RPC_ERROR_MISSING_NAZWA_METODY;

		if (!metoda[METODA_RPC_ID_UNIKALNE].isString())
			return RPC_ERROR_MISSING_ID_UNIKALNE;

		if (!metoda[METODA_RPC_POWTORZENIE].isUInt())
			return RPC_ERROR_MISSING_POWTORZENIE;

		if (!metoda[METODA_RPC_CZAS_WYWOLANIA].isString())
			return RPC_ERROR_MISSING_CZAS_WYWOLANIA;

		if (odpowiedz){
			if (!metoda[METODA_RPC_CZAS_ODPOWIEDZI].isString())
				return RPC_ERROR_MISSING_CZAS_ODPOWIEDZI;

			if (!metoda[METODA_RPC_RETURN].isObject())
				return RPC_ERROR_MISSING_RETURN;
		}

		return RPC_OK;
	}

	int MetodaRPC::sprawdzAutoryzacje(const Json::Value& root){
		if (root[METODA_RPC_AUTORYZACJA].asString() == "0" && root[METODA_RPC_INSTANCJA].asString() == "0")
			return RPC_ERROR_WITHOUT_AUTHORIZED;

		if (root[METODA_RPC_AUTORYZACJA].asString() == "0" || root[METODA_RPC_INSTANCJA].asString() == "0")
			return RPC_ERROR_UNAUTHORIZED;

		return RPC_OK;
	}

	int MetodaRPC::sprawdzMetodeUprzywilejowana(const Json::Value& root){
		auto nazwa = root[METODA_RPC_METODA][METODA_RPC_NAZWA].asString();
		if (nazwa == "Echo" || nazwa == "InicjujLogowanie")
			return RPC_OK;
		return RPC_ERROR_NEED_AUTHORIZATION;
	}

	Json::Value&  MetodaRPC::obiektParametrow(){
		return parametry_;
	}

	bool MetodaRPC::obsluzMetode(Json::Value & root){
		Json::Value result(Json::objectValue);
		obslugaZadania(root, result);
		czas_odpowiedzi_ = SLog::Log::pobierzInstancje().pobierzDateCzas();
		(*this) >> root;
		root[METODA_RPC_METODA][METODA_RPC_RETURN] = result;
		if (typBledu_ == TYPE_RPC_E_SPECIALIZED_BY_METHOD) {
			root[METODA_RPC_ERROR][METODA_RPC_TYPE] = typBledu_;
			root[METODA_RPC_ERROR][METODA_RPC_KOMUNIKAT] = komuniaktBledu_;
			root[METODA_RPC_ERROR][METODA_RPC_NUMER] = numerBledu_;
		}
		return true;
	}

	int MetodaRPC::wykonajMetode(){
		auto ret = wykonajMetode_impl();
		if (ret != RPC_OK){
			if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)){
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, std::string("Error number: ") + std::to_string(ret));
				SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, (*this));
			}
		}
		return ret;
	}

	void MetodaRPC::wlaczKompresje() {
		flagi_ |= FLAGA_KOMPRESJA;
	}

	void MetodaRPC::wlaczAutoryzacje() {
		flagi_ |= FLAGA_SZYFROWANIE;
	}

	int MetodaRPC::obslugaWyjatku(const Json::Value& root){
		const auto &  throwNode = root[METODA_RPC_ERROR];
		if (throwNode.isNull())
			return RPC_OK;
		if (!throwNode.isObject())
			return RPC_ERROR_INVALID_THROW_OBJECT;

		if (throwNode[METODA_RPC_NUMER].isInt()){
			typBledu_ = throwNode[METODA_RPC_TYPE].asInt();
			if (typBledu_ == TYPE_RPC_E_EXCEPTION){
				if (throwNode[METODA_RPC_EXCEPTION_TYPE].isString())
					typWyjatku_ = throwNode[METODA_RPC_EXCEPTION_TYPE].asCString();
			}
		}

		if (throwNode[METODA_RPC_KOMUNIKAT].isString()){
			komuniaktBledu_ = throwNode[METODA_RPC_KOMUNIKAT].asCString();
		}

		if (throwNode[METODA_RPC_NUMER].isInt()){
			numerBledu_ = throwNode[METODA_RPC_NUMER].asInt();
		}

		return typBledu_ == TYPE_RPC_E_SPECIALIZED_BY_METHOD ? RPC_OK : RPC_ERROR_METHOD_THROW;
	}

	void MetodaRPC::ustawBlad(int numer, std::string tresc){
		typBledu_ = TYPE_RPC_E_SPECIALIZED_BY_METHOD;
		komuniaktBledu_ = tresc;
		numerBledu_ = numer;
	}

	int MetodaRPC::wykonajMetode_impl(){
		//Inicjalizacja właściwości.
		powtorzenie_ = 0;
		klient_.autoryzujMetode(instancja_, autoryzacja_);
		czas_wywolania_ = SLog::Log::pobierzInstancje().pobierzDateCzas();

		if (!przygotowanieDoWyslania())
			return RPC_ERROR_PREPROCESSING_FAIL;

		//Budowanie zapytania
		Json::Value procedura;
		(*this) >> procedura;
		Json::FastWriter writer;
		dodajCRC(procedura);

		// Wysłanie metody do serwera i oczekiwanie na zakończenie.
		auto zadanie = std::make_shared<const std::string>(writer.write(procedura));
		auto wiadomoscZwrotna = std::make_shared<std::string>();
		auto czyZakonczono = klient_.dodajZadanie(std::make_shared<std::promise<bool>>(), zadanie, wiadomoscZwrotna, flagi_);
		czyZakonczono.wait();
		if (!czyZakonczono.get())
			return RPC_ERROR_SENDING_FAIL;

		//Parsowanie odpowiedzi
		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(*wiadomoscZwrotna, root))
			return RPC_ERROR_PARSING_FAIL;

		//Sprawdzenie czy serwer odpowiedział wyjątkiem		
		auto throwError = obslugaWyjatku(root);
		if (throwError != RPC_OK)
			return throwError;

		//Walidowanie metody
		auto error = waliduj(root, true);
		if (error != RPC_OK){
			if (error == RPC_ERROR_UNAUTHORIZED || error == RPC_ERROR_NEED_AUTHORIZATION)
				klient_.zakoncz();
			return error;
		}

		(*this) << root;

		//Obsługa odpowiedzi.
		if (!obslugaOdpowiedzi(root[METODA_RPC_METODA][METODA_RPC_RETURN]))
			return RPC_ERROR_RESPONSE_SERVICE_FAIL;

		return RPC_OK;
	}

	bool MetodaRPC::przygotowanieDoWyslania(){
		return true;
	}

	bool MetodaRPC::obslugaOdpowiedzi(const Json::Value &){
		return false;
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
		metoda[METODA_RPC_PARAMETRY] = parametry_;
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
		
		log.dodajPole(NAZWAPOLA(typBledu_), NAZWAKLASY2(typBledu_), std::to_string(typBledu_));
		log.dodajPole(NAZWAPOLA(komuniaktBledu_), "std::string", komuniaktBledu_);
		log.dodajPole(NAZWAPOLA(typWyjatku_), "std::string", typWyjatku_);
		log.dodajPole(NAZWAPOLA(numerBledu_), NAZWAKLASY2(numerBledu_), std::to_string(numerBledu_));

		Json::StyledWriter writer;
		log.dodajPole(NAZWAPOLA(parametry_), "Json", writer.write(parametry_));
		// TODO: log.dodajPole(NAZWAPOLA(klient_), klient_);
		return log.napis();
	}
}
