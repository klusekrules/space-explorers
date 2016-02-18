#include "Aplikacja.h"

#include <io.h>
#include <WinSock2.h>
#include <fstream>

#include "Model\ZmianaPoziomObiektu.h"

#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\Utils.h"
#include "Utils\StaleUstawienAplikacji.h"

#include "TGUI\TGUI.hpp"
#include "Widok\Konsola\Konsola.h"
#include "Widok\Tgui\MySaver.h"
#include "Widok\Tgui\MyLoader.h"

#include "Wyjatki\BladKonfiguracjiAplikacji.h"

#include "Zarzadca\Fabrykator.h"
#include "Narzedzia\ZarzadcaZasobow.h"
#include "Zarzadca\ZarzadcaPluginow.h"
#include "Zarzadca\ZarzadcaUzytkownikow.h"
#include "Zarzadca\ZarzadcaLokacji.h"

#include "MaszynaStanow\Skrypty\LuaSkrypt.h"
#include "MaszynaStanow\Skrypty\DllSkrypt.h"
#include "MaszynaStanow\MaszynaStanow.h"

#include "Siec\RPC\EchoRPC.h"
#include "Siec\RPC\InicjujLogowanieRPC.h"
#include "Siec\RPC\PotwierdzLogowanieRPC.h"
#include "Siec\RPC\SprawdzSumyKontrolneRPC.h"
#include "Siec\RPC\ListaPlikowRPC.h"

#include "Eksport\Export.h"
#include "Eksport\KodyPowrotu.h"
#include "Eksport\IProxyBO.h"
#include "Eksport\ProxyBOKlient.h"
#include "Eksport\ProxyBOSerwer.h"

#define KOMUNIKAT_BLAD_PRZETWARZANIA_ARGUMENTU STyp::Tekst("Podczas przetwarzabua argumentów wyst¹pi³ b³¹d.")
#define KOMUNIKAT_BLAD_PLIKU_KONFIGURACYJNEGO(plik) STyp::Tekst("Nie powiod³o siê wczytywanie pliku konfiguracyjnego: " + plik)
#define KOMUNIKAT_BLAD_FORMATU_DATY STyp::Tekst("Nie poprawny format daty u¿ytej w nazwie pliku logów.")
#define KOMUNIKAT_BLAD_FORMATU_DATY_LOGOW(format) STyp::Tekst("Nie poprawny format daty logów: " + format )
#define KOMUNIKAT_BLAD_LADOWANIA_OPCJI STyp::Tekst("Podczas przetwa¿ania pliku z opcjami wyst¹pi³ b³¹d.")
#define KOMUNIKAT_BLAD_REJESTRACJI_ZMIANY_POZIOMU STyp::Tekst("Nie powiod³a siê rejestracja zmiany sparawdzaj¹cej poziom obiektu.")
#define KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DOMYSLNYCH STyp::Tekst("Nie powiod³a siê rejestracja domyœlnych obiektów zmiany.")
#define KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DODATKOWYCH STyp::Tekst("Nie powiod³a siê rejestracja dodatkowych obiektów zmiany.")
#define KOMUNIKAT_BLAD_BRAK_PLIKU_DANYCH(plik) STyp::Tekst("Plik : " + plik + " z danymi programu nie zosta³ znaleziony!")
#define KOMUNIKAT_BLAD_BRAK_FOLDERU_PLUGINOW(folder) STyp::Tekst("Folder :" + folder + " nie zosta³ znaleziony!")
#define KOMUNIKAT_BLAD_INICJALIZACJI_WINSOCK STyp::Tekst("B³¹d inicjalizcji biblioteki winsock!")
#define KOMUNIKAT_BLAD_NIE_USTAWIONO_TRYBU_APLIKACJI STyp::Tekst("Nie ustawiono trybu aplikacji!")

#define KOMUNIKAT_STATUS_WINSOCK_WERSJA(wersja) ("Wersja WinSock: " + std::to_string(HIBYTE(wersja.wHighVersion)) + "." + std::to_string(LOBYTE(wersja.wHighVersion)))
#define KOMUNIKAT_STATUS_WINSOCK_OPIS(wersja) ("Opis: " + std::string(wersja.szDescription))
#define KOMUNIKAT_STATUS_WINSOCK_STAN_SYSTEMU(wersja) ("Stan systemu: " + std::string(wersja.szSystemStatus))
#define KOMUNIKAT_STATUS_WINSOCK_LICZBA_GNIAZD(wersja) ("Maksymalna liczba gniazd: " + std::to_string(wersja.iMaxSockets))
#define KOMUNIKAT_STATUS_WINSOCK_ROZMIAR_DATAGRAMU(wersja) ("Maksymalny rozmiar datagramu UDP: " + std::to_string(wersja.iMaxUdpDg))

void myPurecallHandler(){
#ifndef LOG_OFF_ALL
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, STyp::Wyjatek(EXCEPTION_PLACE).napis());
#endif
}

void myInvalidParameterHandler(const wchar_t* expression,
	const wchar_t* function,
	const wchar_t* file,
	unsigned int line,
	uintptr_t pReserved)
{
#ifndef LOG_OFF_ALL
	char* c_expression = new char[wcslen(expression) + 1];
	char* c_function = new char[wcslen(function) + 1];
	char* c_file = new char[wcslen(file) + 1];
	wcstombs_s(nullptr, c_expression, wcslen(expression) + 1, expression, wcslen(expression));
	wcstombs_s(nullptr, c_function, wcslen(function) + 1, function, wcslen(function));
	wcstombs_s(nullptr, c_file, wcslen(file) + 1, file, wcslen(file));
	std::stringstream str;
	str << "Invalid parameter detected in function: " << c_function << ". File: " << c_file << ". Line: " << line << ".\nExpression: " << c_expression;
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, str.str());
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, STyp::Wyjatek(EXCEPTION_PLACE).napis());
#endif
}

namespace SpEx{
	Aplikacja::Aplikacja()
		: logger_(SLog::Log::pobierzInstancje()), czyKonsola_(true), konsola_(nullptr),
		fabrykator_(nullptr), instancjaGry_(nullptr), zarzadcaZasobow_(nullptr), zarzadcaUzytkownikow_(nullptr), zarzadcaLokacji_(nullptr),
		plikKonfiguracyjny_("options.xml")
	{
		rejestrujKontrolkiDoTGUI();

		fabrykator_ = std::make_shared<Fabrykator>();
		zarzadcaZasobow_ = std::make_shared<ZarzadcaZasobow>();
		zarzadcaLokacji_ = std::make_shared<ZarzadcaLokacji>();
		zarzadcaUzytkownikow_ = std::make_shared<ZarzadcaUzytkownikow>();

		/* ------- Konfiguracja parametrów programu -------*/
		if (!przetworzArgumenty()){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_PRZETWARZANIA_ARGUMENTU);
		}

		if (!proxy_){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_NIE_USTAWIONO_TRYBU_APLIKACJI);
		}

		if (!ustawienia_.zaladuj(plikKonfiguracyjny_)){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_PLIKU_KONFIGURACYJNEGO(plikKonfiguracyjny_));
		}

		if (ustawienia_[ATRYBUT_JEZYK_APLIKACJI].empty()){
			ustawienia_[ATRYBUT_JEZYK_APLIKACJI] = ATRYBUT_JEZYK_APLIKACJI_DOMYSLNY;
		}

		konfigurujLogger();
		
		if (!zaladujOpcje()){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_LADOWANIA_OPCJI);
		}

		ustawPlikLogow();

		konfigurujKonsole();

		/* ------------------------------------ */

		_set_purecall_handler(myPurecallHandler);
		_set_invalid_parameter_handler(myInvalidParameterHandler);

		/* ------------------------------------ */

#ifndef LOG_OFF_ALL
		logApInfo();
#endif

		inicjalizujWinsock();

		zarzadcaLokacji_->inicjalizuj(ustawienia_);
		zarzadcaZasobow_->inicjalizuj(ustawienia_);
		zarzadcaUzytkownikow_->inicjalizuj(ustawienia_);

		rejestrujTypyZasobow();
		rejestrujMetodyRPC();
		rejestrujTypySkryptow();

		zarzadcaPluginow_ = std::make_shared<ZarzadcaPluginow>(ustawienia_, fabrykator_->pobierzFabrykeZmian(), logger_);

		if (!RejestrujZmianaPoziomObiektu(fabrykator_->pobierzFabrykeZmian(), logger_))
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIANY_POZIOMU);

		if (!zarzadcaPluginow_->zaladujDomyslneKlasyZmian())
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DOMYSLNYCH);

		if (!zarzadcaPluginow_->zaladujZewnetrzneKlasyZmian(*zarzadcaZasobow_))
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DODATKOWYCH);
	}
	
	void Aplikacja::rejestrujKontrolkiDoTGUI(){
		tgui::WidgetSaver::setSaveFunction("BazowyWidzet", tgui::saveBazowyWidzet);
		tgui::WidgetSaver::setSaveFunction("SurowiecGui", tgui::saveSurowiecGui);
		tgui::WidgetSaver::setSaveFunction("KontrolkaObiektu", tgui::saveKontrolkaObiektu);
		tgui::WidgetSaver::setSaveFunction("LogListGui", tgui::saveLogListGui);
		tgui::WidgetSaver::setSaveFunction("ListaSurowcowGui", tgui::saveListaSurowcowGui);
		tgui::WidgetLoader::setLoadFunction("BazowyWidzet", std::bind(tgui::loadBazowyWidzet, std::placeholders::_1, std::shared_ptr<tgui::BazowyWidzet>{}));
		tgui::WidgetLoader::setLoadFunction("SurowiecGui", std::bind(tgui::loadSurowiecGui, std::placeholders::_1, std::shared_ptr<tgui::SurowiecGui>{}));
		tgui::WidgetLoader::setLoadFunction("KontrolkaObiektu", std::bind(tgui::loadKontrolkaObiektu, std::placeholders::_1, std::shared_ptr<tgui::KontrolkaObiektu>{}));
		tgui::WidgetLoader::setLoadFunction("LogListGui", std::bind(tgui::loadLogListGui, std::placeholders::_1, std::shared_ptr<tgui::LogListGui>{}));
		tgui::WidgetLoader::setLoadFunction("ListaSurowcowGui", std::bind(tgui::loadListaSurowcowGui, std::placeholders::_1, std::shared_ptr<tgui::ListaSurowcowGui>{}));
	}

	void Aplikacja::rejestrujParametryKonsoli(){
		parametryUruchomieniowe_.emplace("-O", OpcjeParametru(1, [&](std::vector<char*> lista)->bool{
			if (lista.size() == 0)
				return false;

			auto wsk = lista.begin();
			if (*wsk){
				std::string nazwa(*wsk);
				if (!nazwa.empty()){
					plikKonfiguracyjny_ = nazwa;
					return true;
				}
			}
			return false;
		}));

		parametryUruchomieniowe_.emplace("-T", OpcjeParametru(1, [&](std::vector<char*> lista)->bool{
			if (lista.size() == 0)
				return false;

			auto wsk = lista.begin();
			if (*wsk){
				std::string nazwa(*wsk);
				if (!nazwa.empty()){
					if (nazwa == "Serwer"){
						if (proxy_){
							return proxy_->pobierzTrybAplikacji() == TrybAplikacji::Serwer;
						}
						proxy_ = std::make_shared <ProxyBOSerwer>();
						return true;
					}
					if (nazwa == "Klient"){
						if (proxy_){
							return proxy_->pobierzTrybAplikacji() == TrybAplikacji::Klient;
						}
						proxy_ = std::make_shared <ProxyBOKlient>();
						return true;
					}
				}
			}
			return false;
		}));

		parametryUruchomieniowe_.emplace("-NoConsola", OpcjeParametru(0, [&](std::vector<char*> lista)->bool{
			czyKonsola_ = false;
			return true;
		}));
	}

	bool Aplikacja::przetworzArgumenty(){
		if (!argumenty || iloscArgumentow <= 0)
			return false;

		rejestrujParametryKonsoli();

		for (int numer = 0; numer < iloscArgumentow; ++numer){
			if (!argumenty[numer])
				continue;
			std::string argument(argumenty[numer]);
			if (argument.empty())
				continue;
			auto parametr = parametryUruchomieniowe_.find(argument);
			if (parametr == parametryUruchomieniowe_.end())
				continue;
			if (parametr->second.iloscParametrow_ + numer >= iloscArgumentow)
				return false;
			std::vector<char*> lista;
			lista.reserve(parametr->second.iloscParametrow_);
			for (unsigned char offset = 1; offset <= parametr->second.iloscParametrow_; ++offset){
				lista.push_back(argumenty[numer + offset]);
			}
			if (parametr->second.funkcja_(lista))
				numer += parametr->second.iloscParametrow_;
			else
				return false;
		}
		return true;
	}

	void Aplikacja::konfigurujLogger(){
		auto i = std::stol(ustawienia_[ATRYBUT_NUMER_FORMATU_DATY], nullptr, 10);
		switch (i)
		{
		case SLog::Log::Data: logger_.ustawFormatCzasu(SLog::Log::Data);
			break;
		case SLog::Log::Czas: logger_.ustawFormatCzasu(SLog::Log::Czas);
			break;
		case SLog::Log::DataCzas: logger_.ustawFormatCzasu(SLog::Log::DataCzas);
			break;
		default:
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_FORMATU_DATY_LOGOW(std::to_string(i)));
			break;
		}

		for (auto typ : Utils::dekodujListeTypowLogow(ustawienia_[ATRYBUT_ODBLOKOWANE_LOGI])){
			logger_.odblokujLogi(typ);
		}

		for (auto typ : Utils::dekodujListeTypowLogow(ustawienia_[ATRYBUT_ZABLOKOWANE_LOGI])){
			logger_.zablokujLogi(typ);
		}
	}

	bool Aplikacja::zaladujOpcje(){
		try{
			std::locale pl(ustawienia_[ATRYBUT_JEZYK_APLIKACJI]);
			std::locale::global(pl);
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
			logger_.loguj(SLog::Log::Debug, std::string("Separator u³amka: ") + std::use_facet<std::numpunct<char>>(pl).decimal_point());
#endif
			auto nazwaPlikuDanych_ = ustawienia_[ATRYBUT_PLIK_DANYCH];
			if (_access(nazwaPlikuDanych_.c_str(), 0) == -1){ // Sprawdzenie czy folder istnieje
				throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_BRAK_PLIKU_DANYCH(nazwaPlikuDanych_));
			}

			auto folderPluginow_ = ustawienia_[ATRYBUT_FOLDER_PLUGINOW];
			if (_access(folderPluginow_.c_str(), 0) == -1){ // Sprawdzenie czy folder istnieje
				throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_BRAK_FOLDERU_PLUGINOW(folderPluginow_));
			}
		}
		catch (std::exception &e){
#ifndef LOG_OFF_ALL
			logger_.loguj(SLog::Log::Error, e.what());
#endif
			return false;
		}
		return true;
	}

	void Aplikacja::ustawPlikLogow(){
		struct tm timeinfo;
		time_t t = time(nullptr);
		localtime_s(&timeinfo, &t);
		char s[20];
		if (strftime(s, 20, ustawienia_[ATRYBUT_FORMAT_DATY_LOGOW].c_str(), &timeinfo) == 0){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_FORMATU_DATY);
		}

		std::stringstream sfile;
		sfile << ustawienia_[ATRYBUT_PRZEDROSTEK_PLIKU_LOGOW] << s << ".log";
		std::string filename = sfile.str();
		logger_.dodajGniazdoWyjsciowe([filename](SLog::Log::TypLogow typ, const std::string& czas, const std::string& komunikat)->void{
			static std::fstream plik(filename, std::fstream::app);
			std::string sTyp;
			switch (typ)
			{
			case SLog::Log::Debug: sTyp = " [DEBUG] ";
				break;
			case SLog::Log::Info: sTyp = " [INFO] ";
				break;
			case SLog::Log::Warning: sTyp = " [WARNING] ";
				break;
			case SLog::Log::Error: sTyp = " [ERROR] ";
				break;
			case SLog::Log::All:
			default:
				break;
			}
			plik << czas << sTyp << komunikat << std::endl;
		});

	}
		
	void Aplikacja::konfigurujKonsole(){		
		if (czyKonsola_){
			konsola_ = std::make_shared<Konsola>(logger_);
			konsola_->czekajNaInicjalizacje();
		} else{
			konsola_ = nullptr;
		}
	}

	void Aplikacja::inicjalizujWinsock(){
		WORD RequiredVersion;
		WSADATA WData;

		RequiredVersion = MAKEWORD(2, 0);

		if (WSAStartup(RequiredVersion, &WData) != 0) {
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, pobierzDebugInfo(), KOMUNIKAT_BLAD_INICJALIZACJI_WINSOCK);
		}
	}

	void Aplikacja::rejestrujTypyZasobow(){

		zarzadcaZasobow_->dodajCallback([](const std::string& nazwa, Zasob::SharedPtr)->void{
			SLog::Log::pobierzInstancje().loguj(SLog::Log::Info, "Zarejestrowano zasób: " + nazwa);
		}, StrukturyZarzadcyZasobow::PoRejestracji);

		zarzadcaZasobow_->rejestrujTypyWbudowane();
	}

	void Aplikacja::rejestrujMetodyRPC(){
		fabrykator_->rejestrujMetodeRPC<EchoRPC>();
		fabrykator_->rejestrujMetodeRPC<InicjujLogowanieRPC>();
		fabrykator_->rejestrujMetodeRPC<PotwierdzLogowanieRPC>();
		fabrykator_->rejestrujMetodeRPC<SprawdzSumyKontrolneRPC>();
		fabrykator_->rejestrujMetodeRPC<ListaPlikowRPC>();
	}

	void Aplikacja::rejestrujTypySkryptow(){
		fabrykator_->rejestrujSkrypt<DllSkrypt>();
		fabrykator_->rejestrujSkrypt<LuaSkrypt>();
	}
	
}