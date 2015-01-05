#include "MetodaRPC.h"
#include "Logger\Log.h"

#define BRAK_ELEMENTU(n) "MetodaRPC::odczytajWezel -> " + std::string(n)
#define METODA_RPC_ID "id"
#define METODA_RPC_NAZWA "nazwa"
#define METODA_RPC_ID_UNIKALNE "id-unikalne"
#define METODA_RPC_POWTORZENIE "powtorzenie"
#define METODA_RPC_CZAS_WYWOLANIA "czas-wywolania"
#define METODA_RPC_CZAS_ODPOWIEDZI "czas-odpowiedzi"
#define METODA_RPC_PARAMETRY "parametry"

namespace SpEx{

	bool MetodaRPC::odczytajWezel(const Json::Value & root){
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

}
