#include "ProxyBOSerwer.h"
#include "KodyPowrotu.h"
#include "Kontroler\Siec\Serwer.h"
#include "Kontroler\Siec\Klient.h"
#include "Kontroler\Aplikacja.h"
#include "Widok\Konsola\Konsola.h"
#include "Export.h"

namespace SpEx{

	ProxyBOSerwer::ProxyBOSerwer(){
	
	}

	int ProxyBOSerwer::uruchomSerwer(){
		if (serwer_){
			return RETURN_CODE_SERWER_JUZ_JEST_WLACZONY;
		}
		
		serwer_ = std::make_shared<Serwer>(Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji());
		serwer_->odblokuj();
		return RETURN_CODE_OK;
	}

	int ProxyBOSerwer::zatrzymajSerwer(){
		if (!serwer_){
			return RETURN_CODE_SERWER_JUZ_JEST_WYLACZONY;
		}
		serwer_->zakoncz();
		serwer_->czekajNaZakonczenie();
		serwer_ = nullptr;
		return RETURN_CODE_OK;
	}

	int ProxyBOSerwer::polaczDoSerwera(const char* ip, unsigned short port) {
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}

	int ProxyBOSerwer::rozlaczOdSerwera() {
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}

	int ProxyBOSerwer::posptrzataj(){
		return zatrzymajSerwer();
	}

	int ProxyBOSerwer::rejestrujMetodyKonsoli(){

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

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("start", Konsola::OpcjePolecenia("uruchom serwer", [&](std::string){
			auto ret = uruchomSerwer();
			switch (ret){
			case RETURN_CODE_OK:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Ok");
				break;
			case RETURN_CODE_SERWER_JUZ_JEST_WLACZONY:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Serwer jest ju¿ w³¹czony");
				break;
			case RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Aplikacja uruchomiona w z³ym trybie");
				break;
			default:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Nierozpoznany kod powrotu: " + std::to_string(ret));
				break;
			}
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("stop", Konsola::OpcjePolecenia("zatrzymaj serwer", [&](std::string){
			auto ret = zatrzymajSerwer();
			switch (ret){
			case RETURN_CODE_OK:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Ok");
				break;
			case RETURN_CODE_SERWER_JUZ_JEST_WYLACZONY:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Serwer jest ju¿ wy³¹czony");
				break;
			default:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Nierozpoznany kod powrotu: " + std::to_string(ret));
				break;
			}
		}));
		return RETURN_CODE_OK;
	}

	int ProxyBOSerwer::zaloguj(const char * nazwa, const char* hash){
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}
	
	TrybAplikacji ProxyBOSerwer::pobierzTrybAplikacji(){
		return TrybAplikacji::Serwer;
	}
}
