#include "ProxyBOKlient.h"
#include "KodyPowrotu.h"
#include "Kontroler\Siec\Serwer.h"
#include "Kontroler\Siec\Klient.h"
#include "Kontroler\Aplikacja.h"
#include "Widok\Konsola\Konsola.h"
#include "Export.h"
#include "Kontroler\Siec\RPC\StaleRPC.h"
#include "Kontroler\Siec\RPC\ListaPlikowRPC.h"
#include "Kontroler\Siec\RPC\PobierzPlikRPC.h"
#include "Kontroler\Siec\RPC\InicjujLogowanieRPC.h"
#include "Kontroler\Siec\RPC\PotwierdzLogowanieRPC.h"
#include "Kontroler\Siec\RPC\SprawdzSumyKontrolneRPC.h"
#include "Kontroler\Zarzadca\Fabrykator.h"
#include "Algorytmy\SHA3.h"
#include "Algorytmy\Hex.h"
#include "Utils\StaleUstawienAplikacji.h"

namespace SpEx{
	int ProxyBOKlient::uruchomSerwer(){
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}

	int ProxyBOKlient::zatrzymajSerwer(){
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}

	int ProxyBOKlient::polaczDoSerwera(const char* ip, unsigned short port) {
		int returnCode = RETURN_CODE_OK;
		if (klient_ && !klient_->zakonczony()){
			return RETURN_CODE_ISTNIEJE_POLACZENIE;
		}
		if (klient_){
			klient_->zakoncz();
			klient_->czekajNaZakonczenie();
		}
		if (ip != nullptr)
			klient_ = std::make_shared<Klient>(ip, port);
		else
			klient_ = std::make_shared<Klient>(Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji());
		if (klient_->blad()) {
			klient_->zakoncz();
			returnCode = klient_->bladInfo().getNumerWyjaku()();
		}
		klient_->odblokuj();
		return returnCode;
	}

	int ProxyBOKlient::rozlaczOdSerwera() {
		if (!klient_){
			return RETURN_CODE_BRAK_POLACZENIA;
		}
		klient_->zakoncz();
		klient_->czekajNaZakonczenie();
		klient_ = nullptr;
		return RETURN_CODE_OK;
	}

	int ProxyBOKlient::posptrzataj(){
		return rozlaczOdSerwera();
	}

	int ProxyBOKlient::rejestrujMetodyKonsoli(){

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("zamknij", Konsola::OpcjePolecenia("zamykanie aplikacji", [&](std::string){
			posptrzataj();
			zamknijAplikacje();
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("info", Konsola::OpcjePolecenia("informacje o aplikacji", [&](std::string){
			Aplikacja::pobierzInstancje().logApInfo();
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("metody", Konsola::OpcjePolecenia("lista poleceñ", [&](std::string){
			Aplikacja::pobierzInstancje().konsola_->logujListePolecen();
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("po³¹cz", Konsola::OpcjePolecenia("po³acz siê z serwerem", [&](std::string param){
			int ret = RETURN_CODE_OK;
			if (!param.empty()){
				auto pos = param.find_first_of(':');
				ret = polaczDoSerwera(param.substr(0, pos).c_str(), static_cast<unsigned short>(std::strtol(param.substr(pos + 1).c_str(), 0, 10)));
			} else{
				ret = polaczDoSerwera(nullptr,0);
			}
			switch (ret){
			case RETURN_CODE_OK:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Ok");
				break;
			case RETURN_CODE_ISTNIEJE_POLACZENIE:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Jest ju¿ nawi¹zane po³¹czenie.");
				break;
			case RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Aplikacja uruchomiona w z³ym trybie");
				break;
			default:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Nierozpoznany kod powrotu: " + std::to_string(ret));
				break;
			}
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("roz³¹cz", Konsola::OpcjePolecenia("roz³¹cz siê z serwerem", [&](std::string){
			auto ret = rozlaczOdSerwera();
			switch (ret){
			case RETURN_CODE_OK:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Ok");
				break;
			case RETURN_CODE_BRAK_POLACZENIA:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Brak po³¹czenia");
				break;
			default:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Nierozpoznany kod powrotu: " + std::to_string(ret));
				break;
			}
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("zaloguj", Konsola::OpcjePolecenia("logowanie do serwera", [&](std::string param){
			auto pos = param.find_first_of(' ');
			std::string haslo(param.substr(pos + 1));
			SHA3 sha3(haslo);
			haslo = sha3.pobierzNapis<Hex>();
			auto ret = zaloguj(param.substr(0, pos).c_str(), haslo.c_str());
			if (ret == RETURN_CODE_OK){
				ret = sprawdzPoprawnoscPlikow();
			}
			switch (ret){
			case RETURN_CODE_OK:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Zalogowano!");
				break;
			case RETURN_CODE_BRAK_POLACZENIA:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Brak po³¹czenia");
				break;
			case RPC_ERROR_SENDING_FAIL:
				if (klient_->kodPowrotu() == RPC_ERROR_DECRYPTION_FAIL){
					Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Error, "Niepoprawny login lub has³o!");
					if (rozlaczOdSerwera() == RETURN_CODE_OK){
						Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");						
					}
					break;
				}
			default:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Nierozpoznany kod powrotu: " + std::to_string(ret));
				if (rozlaczOdSerwera() == RETURN_CODE_OK){
					Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Zamkniêto po³¹czenie!");
				}
				break;
			}

			
		}));
		return RETURN_CODE_OK;
	}

	int ProxyBOKlient::zaloguj(const char * nazwa, const char* hash){

		if (!klient_)
			return RETURN_CODE_BRAK_POLACZENIA;

		if (!nazwa && !hash)
			return RETURN_CODE_BRAK_ATRYBUTOW;

		auto init = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::InicjujLogowanieRPC>(*klient_);
		if (!init){
			return RETURN_CODE_BRAK_METOD;
		}
		auto conf = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::PotwierdzLogowanieRPC>(*klient_);
		if (!conf){
			return RETURN_CODE_BRAK_METOD;
		}
		init->obiektParametrow()["Login"] = nazwa;
		init->obiektParametrow()["Hash"] = hash;
		auto ret = init->wykonajMetode();
		int retCode = klient_->kodPowrotu();
		if (ret == RPC_OK && retCode == RPC_OK){
			ret = conf->wykonajMetode();
			retCode = klient_->kodPowrotu();
		}
		if (retCode != RPC_OK){
			Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "retCode: " + std::to_string(retCode));
		}
		return ret;
	}

	int ProxyBOKlient::sprawdzPoprawnoscPlikow(){
		if (!klient_)
			return RETURN_CODE_BRAK_POLACZENIA;

		auto listaplikow = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::ListaPlikowRPC>(*klient_);
		if (!listaplikow){
			return RETURN_CODE_BRAK_METOD;
		}
		auto sprawdzSumy = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::SprawdzSumyKontrolneRPC>(*klient_);
		if (!sprawdzSumy){
			return RETURN_CODE_BRAK_METOD;
		}
		auto ret = listaplikow->wykonajMetode();
		int retCode = klient_->kodPowrotu();
		if (ret == RPC_OK && retCode == RPC_OK){
			sprawdzSumy->ustawListePlikow(listaplikow->pobierzListePlikow());
			ret = sprawdzSumy->wykonajMetode();
			retCode = klient_->kodPowrotu();
		}
		if (retCode != RPC_OK){
			Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "retCode: " + std::to_string(retCode));
		}
		return ret;

	}

	TrybAplikacji ProxyBOKlient::pobierzTrybAplikacji(){
		return TrybAplikacji::Klient;
	}

	int ProxyBOKlient::pobierzPlikiGry()
	{
		if (!klient_)
			return RETURN_CODE_BRAK_POLACZENIA;

		auto listaplikow = SpEx::Aplikacja::pobierzInstancje().pobierzFabrykator().tworzMetodeRPC<SpEx::PobierzPlikRPC>(*klient_);
		if (!listaplikow) {
			return RETURN_CODE_BRAK_METOD;
		}

		listaplikow->obiektParametrow()["Plik"] = ATRYBUT_PLIK_DANYCH;

		listaplikow->wykonajMetode();

		return RETURN_CODE_OK;
	}
}