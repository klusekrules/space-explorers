#include "ProxyBOSerwer.h"
#include "KodyPowrotu.h"
#include "Kontroler\Siec\Serwer\SerwerMulti.h"
#include "Kontroler\Aplikacja.h"
#include "Kontroler\Zarzadca\ZarzadcaLokacji.h"
#include "Widok\Konsola\Konsola.h"
#include "Export.h"
#include "Utils\UtilsGui.h"

namespace SpEx{

	ProxyBOSerwer::ProxyBOSerwer(){
	
	}

	int ProxyBOSerwer::uruchomSerwer(){
		if (serwer_){
			return RETURN_CODE_SERWER_JUZ_JEST_WLACZONY;
		}
		
		if (Aplikacja::pobierzInstancje().pobierzZarzadceLokacji().pobierzIloscGalaktyk() == 0) {
			Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Wykryto brak galaktyki. Rozpocz�cie generowania galaktyki.");
			if (Aplikacja::pobierzInstancje().pobierzZarzadceLokacji().generujNowaGalaktyke())
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Uda�o si� wygenerowa� galaktyk�.");
			else
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "B��d podczas generowania galaktyki.");
		}

		serwer_ = std::make_shared<SerwerMulti>(Aplikacja::pobierzInstancje().pobierzUstawieniaAplikacji());
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

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("test", Konsola::OpcjePolecenia("Test kontrolek", [&](std::string) {
			UtilsGui::oknotestowe();
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("zamknij", Konsola::OpcjePolecenia("zamykanie aplikacji", [&](std::string){
			posptrzataj();
			zamknijAplikacje();
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("info", Konsola::OpcjePolecenia("informacje o aplikacji", [&](std::string){ 
			Aplikacja::pobierzInstancje().logApInfo(); 
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("metody", Konsola::OpcjePolecenia("lista polece�", [&](std::string){
			Aplikacja::pobierzInstancje().konsola_->logujListePolecen();
		}));

		Aplikacja::pobierzInstancje().konsola_->rejestrujPolecenie("start", Konsola::OpcjePolecenia("uruchom serwer", [&](std::string){
			auto ret = uruchomSerwer();
			switch (ret){
			case RETURN_CODE_OK:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Info, "Ok");
				break;
			case RETURN_CODE_SERWER_JUZ_JEST_WLACZONY:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Serwer jest ju� w��czony");
				break;
			case RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI:
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Aplikacja uruchomiona w z�ym trybie");
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
				Aplikacja::pobierzInstancje().logger_.loguj(SLog::Log::Warning, "Serwer jest ju� wy��czony");
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

	int ProxyBOSerwer::sprawdzPoprawnoscPlikow(){
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}
	
	TrybAplikacji ProxyBOSerwer::pobierzTrybAplikacji(){
		return TrybAplikacji::Serwer;
	}

	int ProxyBOSerwer::pobierzPlikiGry(){
		return RETURN_CODE_NIEODPOWIEDNI_TRYB_APLIKACJI;
	}
}
