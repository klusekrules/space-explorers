#include "ProxyBOKlient.h"
#include "KodyPowrotu.h"
#include "Kontroler\Siec\Serwer.h"
#include "Kontroler\Siec\Klient.h"
#include "Kontroler\Aplikacja.h"
#include "Widok\Konsola\Konsola.h"
#include "Export.h"
namespace SpEx{
	int ProxyBOKlient::uruchomSerwer(){
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}

	int ProxyBOKlient::zatrzymajSerwer(){
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}

	int ProxyBOKlient::polaczDoSerwera(const char* ip, unsigned short port) {
		if (klient_){
			return RETURN_CODE_ISTNIEJE_POLACZENIE;
		}
		
		klient_ = std::make_shared<Klient>(ip, port);
		klient_->odblokuj();
		return RETURN_CODE_OK;
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

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("po��cz", Konsola::OpcjePolecenia("po�acz si� z serwerem", [&](std::string param){
			auto pos = param.find_first_of(':');
			auto ret = polaczDoSerwera(param.substr(0, pos).c_str(), static_cast<unsigned short>(std::strtol(param.substr(pos + 1).c_str(), 0, 10)));
			switch (ret){
			case RETURN_CODE_OK:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Ok");
				break;
			case RETURN_CODE_ISTNIEJE_POLACZENIE:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Jest ju� nawi�zane po��czenie.");
				break;
			case RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Aplikacja uruchomiona w z�ym trybie");
				break;
			default:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Nierozpoznany kod powrotu: " + std::to_string(ret));
				break;
			}
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("roz��cz", Konsola::OpcjePolecenia("roz��cz si� z serwerem", [&](std::string){
			auto ret = rozlaczOdSerwera();
			switch (ret){
			case RETURN_CODE_OK:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Ok");
				break;
			case RETURN_CODE_BRAK_POLACZENIA:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Brak po��czenia");
				break;
			default:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Nierozpoznany kod powrotu: " + std::to_string(ret));
				break;
			}
		}));
		return RETURN_CODE_OK;
	}

	TrybAplikacji ProxyBOKlient::pobierzTrybAplikacji(){
		return TrybAplikacji::Klient;
	}
}