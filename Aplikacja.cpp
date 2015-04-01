#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <io.h>
#include <WinSock2.h>

#include "ZmianaPoziomObiektu.h"
#include "DefinicjeWezlowXML.h"
#include "TGUI\TGUI.hpp"
#include "ListaObiektowGui.h"
#include "ListaSurowcowGui.h"
#include "LogListGui.h"
#include "BladKonfiguracjiAplikacji.h"
#include "LuaState.h"
#include "DllModule.h"
#include "XmlModul.h"
#include "LuaSkrypt.h"
#include "DllSkrypt.h"
#include "SumaKontrolnaPliku.h"
#include "MaszynaStanow.h"

#include "EchoRPC.h"
#include "InicjujLogowanieRPC.h"
#include "PotwierdzLogowanieRPC.h"
#include "SprawdzSumyKontrolneRPC.h"

#include "Fabrykator.h"
#include "ZarzadcaZasobow.h"
#include "Gra.h"
#include "ZarzadcaPluginow.h"
#include "ZarzadcaUzytkownikow.h"
#include "ZarzadcaLokacji.h"

#include "Utils.h"
#include "StaleUstawienAplikacji.h"
#include "Konsola.h"
#include "Export.h"

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
#define KOMUNIKAT_BLAD_INICJALIZACJI_WINSOCK STyp::Tekst("B³¹d inicjalizcji biblioteki winsock")

#define KOMUNIKAT_STATUS_WINSOCK_WERSJA(wersja) ("Wersja WinSock: " + std::to_string(HIBYTE(wersja.wHighVersion)) + "." + std::to_string(LOBYTE(wersja.wHighVersion)))
#define KOMUNIKAT_STATUS_WINSOCK_OPIS(wersja) ("Opis: " + std::string(wersja.szDescription))
#define KOMUNIKAT_STATUS_WINSOCK_STAN_SYSTEMU(wersja) ("Stan systemu: " + std::string(wersja.szSystemStatus))
#define KOMUNIKAT_STATUS_WINSOCK_LICZBA_GNIAZD(wersja) ("Maksymalna liczba gniazd: " + std::to_string(wersja.iMaxSockets))
#define KOMUNIKAT_STATUS_WINSOCK_ROZMIAR_DATAGRAMU(wersja) ("Maksymalny rozmiar datagramu UDP: " + std::to_string(wersja.iMaxUdpDg))

void myPurecallHandler(){
#ifndef LOG_OFF_ALL
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, SpEx::Aplikacja::pobierzInstancje().pobierzSladStosu());
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
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, SpEx::Aplikacja::pobierzInstancje().pobierzSladStosu());
#endif
}

namespace SpEx{

	int Aplikacja::iloscArgumentow = 0;
	char** Aplikacja::argumenty = nullptr;

	Aplikacja::Aplikacja()
		: czyZainicjalizowanaBiblioteka_(false), logger_(SLog::Log::pobierzInstancje()), czyKonsola_(true), konsola_(nullptr),
		fabrykator_(nullptr), instancjaGry_(nullptr), zarzadcaZasobow_(nullptr), zarzadcaUzytkownikow_(nullptr), zarzadcaLokacji_(nullptr),
		plikKonfiguracyjny_("options.xml")
	{
		tgui::TGUI_WidgetFactory.RejestrujKreatorWidzetu("listasurowcowgui", tgui::ListaSurowcowGui::createWidget);
		tgui::TGUI_WidgetFactory.RejestrujKreatorWidzetu("listaobiektowgui", tgui::ListaObiektowGui::createWidget);
		tgui::TGUI_WidgetFactory.RejestrujKreatorWidzetu("kontrolkaobiektu", tgui::KontrolkaObiektu::createWidget);
		tgui::TGUI_WidgetFactory.RejestrujKreatorWidzetu("loglistgui", tgui::LogListGui::createWidget);
		
		fabrykator_ = std::make_shared<Fabrykator>();
		zarzadcaZasobow_ = std::make_shared<ZarzadcaZasobow>();
		zarzadcaLokacji_ = std::make_shared<ZarzadcaLokacji>();
		zarzadcaUzytkownikow_ = std::make_shared<ZarzadcaUzytkownikow>();

		/* ------------------------------------------ */

		//Ladowanie potrzebnych bibliotek
		uchwyt_ = LoadLibrary("Dbghelp.dll");
		if (uchwyt_){
			symInitialize_ = (SymInitializeS)GetProcAddress(uchwyt_, "SymInitialize");
			symFromAddr_ = (SymFromAddrS)GetProcAddress(uchwyt_, "SymFromAddr");
			if (symFromAddr_ && symInitialize_){
				czyZainicjalizowanaBiblioteka_ = true;
			}
		}
		
		/* ------- Konfiguracja parametrów programu -------*/
		if (!przetworzArgumenty()){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_PRZETWARZANIA_ARGUMENTU);
		}

		if (!ustawienia_.zaladuj(plikKonfiguracyjny_)){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_PLIKU_KONFIGURACYJNEGO(plikKonfiguracyjny_));
		}

		if (ustawienia_[ATRYBUT_JEZYK_APLIKACJI].empty()){
			ustawienia_[ATRYBUT_JEZYK_APLIKACJI] = ATRYBUT_JEZYK_APLIKACJI_DOMYSLNY;
		}

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
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_FORMATU_DATY_LOGOW(std::to_string(i)));
			break;
		}
		
		for (auto typ : Utils::dekodujListeTypowLogow(ustawienia_[ATRYBUT_ODBLOKOWANE_LOGI])){
			logger_.odblokujLogi(typ);
		}

		for (auto typ : Utils::dekodujListeTypowLogow(ustawienia_[ATRYBUT_ZABLOKOWANE_LOGI])){
			logger_.zablokujLogi(typ);
		}

		if (!zaladujOpcje()){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_LADOWANIA_OPCJI);
		}

		/* ------- Przypisanie pliku do którego bêd¹ dodawane logi ------- */

		struct tm timeinfo;
		time_t t = time(nullptr);
		localtime_s(&timeinfo, &t);
		char s[20];
		if (strftime(s, 20, ustawienia_[ATRYBUT_FORMAT_DATY_LOGOW].c_str(), &timeinfo) == 0){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_FORMATU_DATY);
		}

		std::stringstream sfile;
		sfile << ustawienia_[ATRYBUT_PRZEDROSTEK_PLIKU_LOGOW] << s << ".log";
		std::string filename = sfile.str();
		logger_.dodajGniazdoWyjsciowe([&filename](SLog::Log::TypLogow typ, const std::string& czas, const std::string& komunikat)->void{
			static std::fstream plik(filename, std::ios_base::app);
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

		if (czyKonsola_){
			poleceniaKonsoli_.emplace("zamknij", [](std::string){ zamknijAplikacje(); });
			konsola_ = std::make_shared<Konsola>(logger_);
		} else{
			konsola_ = nullptr;
		}
		
		/* ------------------------------------ */

		_set_purecall_handler(myPurecallHandler);
		_set_invalid_parameter_handler(myInvalidParameterHandler);

		/* ------------------------------------ */
#ifndef LOG_OFF_ALL
		logger_.loguj(SLog::Log::Info, "Start aplikacji Space-Explorers.");
#endif
		//Wyswietlanie informacji o aplikacji
		logApInfo();

		WORD RequiredVersion;
		WSADATA WData;

		RequiredVersion = MAKEWORD(2, 0);

		if (WSAStartup(RequiredVersion, &WData) != 0) {
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_INICJALIZACJI_WINSOCK);
		}
				
#ifndef LOG_OFF_ALL
		//Wyswietlanie informacji o zaladowanej bibliotece
		if (uchwyt_){
			if (czyZainicjalizowanaBiblioteka_){
				logger_.loguj(SLog::Log::Info, "Za³adowano biblioteke Dbghelp.dll");
			}
			else{
				logger_.loguj(SLog::Log::Warning, "Nie zanaleziono funkcji SymInitialize i/lub SymFromAddr.");
			}
		}
		else{
			logger_.loguj(SLog::Log::Warning, "Nie za³adowano biblioteki Dbghelp.dll");
		}
#endif
		zarzadcaLokacji_->inicjalizuj(ustawienia_, std::bind(&Aplikacja::pobierzSladStosu, this));
		zarzadcaZasobow_->inicjalizuj(ustawienia_, std::bind(&Aplikacja::pobierzSladStosu, this));
		zarzadcaUzytkownikow_->inicjalizuj(ustawienia_, std::bind(&Aplikacja::pobierzSladStosu, this));

		zarzadcaZasobow_->rejestruj<LuaState>();
		zarzadcaZasobow_->rejestruj<DllModule>();
		zarzadcaZasobow_->rejestruj<XmlModul>();
		zarzadcaZasobow_->rejestruj<SumaKontrolnaPliku>();

		/* ------- Rejestrowanie zdalnych metod -------*/
		fabrykator_->rejestrujMetodeRPC<EchoRPC>();
		fabrykator_->rejestrujMetodeRPC<InicjujLogowanieRPC>();
		fabrykator_->rejestrujMetodeRPC<PotwierdzLogowanieRPC>();
		fabrykator_->rejestrujMetodeRPC<SprawdzSumyKontrolneRPC>();
		fabrykator_->rejestrujSkrypt<DllSkrypt>();
		fabrykator_->rejestrujSkrypt<LuaSkrypt>();

		zarzadcaPluginow_ = std::make_shared<ZarzadcaPluginow>(ustawienia_, fabrykator_->pobierzFabrykeZmian(), logger_);

		if (!RejestrujZmianaPoziomObiektu(fabrykator_->pobierzFabrykeZmian(), logger_))
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIANY_POZIOMU);

		if (!zarzadcaPluginow_->zaladujDomyslneKlasyZmian())
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DOMYSLNYCH);

		if (!zarzadcaPluginow_->zaladujZewnetrzneKlasyZmian(*zarzadcaZasobow_))
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DODATKOWYCH);

		instancjaGry_ = std::make_shared<Gra>(logger_, *zarzadcaLokacji_, ustawienia_);
	}

	void Aplikacja::wyczyscDane(){
		instancjaGry_ = std::make_shared<Gra>(logger_, *zarzadcaLokacji_, ustawienia_);
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
				throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_BRAK_PLIKU_DANYCH(nazwaPlikuDanych_));
			}

			auto folderPluginow_ = ustawienia_[ATRYBUT_FOLDER_PLUGINOW];
			if (_access(folderPluginow_.c_str(), 0) == -1){ // Sprawdzenie czy folder istnieje
				throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_BRAK_FOLDERU_PLUGINOW(folderPluginow_));
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

	std::string Aplikacja::pobierzDebugInfo() const{
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
		return std::move(Aplikacja::napis() + " " +  MaszynaStanow::pobierzInstancje().napis());
#else
		return std::string();
#endif
	}

	std::string Aplikacja::pobierzSladStosu() const{
		std::stringstream stackTrace;
		if (czyZainicjalizowanaBiblioteka_)
		{
			void *stack[150];
			unsigned short frames;
			SYMBOL_INFO *symbol;
			HANDLE hProcess;
			std::locale l("C");
			stackTrace.imbue(l);
			hProcess = GetCurrentProcess();
			symInitialize_(hProcess, nullptr, true);
			frames = CaptureStackBackTrace(0, 150, stack, nullptr);
			symbol = (SYMBOL_INFO *)calloc(sizeof (SYMBOL_INFO)+256 * sizeof (char), 1);
			symbol->MaxNameLen = 255;
			symbol->SizeOfStruct = sizeof (SYMBOL_INFO);
			if (frames > 0){
				time_t rawtime;
				char buf[30];
				time(&rawtime);
				ctime_s(buf, 30, &rawtime);
				stackTrace << buf;
				// i = 1 - Pominiêcie wywo³ania funkcji getStackTrace
				// i = 0 - W³¹cznie do wyœwietlanego wyniku wywo³ania funkcji getStackTrace
				for (unsigned int i = 1; i < frames; i++)
				{
					symFromAddr_(hProcess, (DWORD_PTR)(stack[i]), 0, symbol);
					stackTrace << std::dec << (unsigned short)(frames - i - 1) << ": 0x" << std::setfill('0') << std::setw(8) << stack[i] << " " << (char*)(symbol->Name) << " = 0x" << std::setfill('0') << std::setw(8) << std::hex << symbol->Address << std::endl;
				}
			}
			free(symbol);
		}
		return stackTrace.str();
	}

	Aplikacja::~Aplikacja()
	{
		if (konsola_){
			konsola_->zakoncz();
			konsola_->czekajNaZakonczenie();
		}

		if (uchwyt_)
			FreeLibrary(uchwyt_);

		WSACleanup();
	}

	bool Aplikacja::zapiszGre(){
		std::locale::global(std::locale("C"));
		try{
			auto dokumentGry = std::make_shared<SPar::ParserDokumentXml>();
			auto wezel = dokumentGry->tworzElement(WEZEL_XML_ROOT);
			if (!wezel){
				return false;
			}

			if (instancjaGry_){
				if(!instancjaGry_->zapiszGracza())
					return false;
			}

			if (!zarzadcaUzytkownikow_->zapiszDane())
				return false;

			if (zarzadcaLokacji_->zapisz(wezel->tworzElement(WEZEL_XML_GRA))){
				std::locale::global(std::locale(ustawienia_[ATRYBUT_JEZYK_APLIKACJI]));
				return dokumentGry->zapisz(ustawienia_[ATRYBUT_PLIK_GRY].c_str());
			}
			
		}
		catch (...){
			std::locale::global(std::locale(ustawienia_[ATRYBUT_JEZYK_APLIKACJI]));
			throw;
		}
		std::locale::global(std::locale(ustawienia_[ATRYBUT_JEZYK_APLIKACJI]));
		return false;
	}

	bool Aplikacja::wczytajGre(std::shared_ptr<SPar::ParserElement> root){
		auto dokumentGry = std::make_shared<SPar::ParserDokumentXml>();
		if (!dokumentGry->odczytaj(ustawienia_[ATRYBUT_PLIK_GRY].c_str())){
			dokumentGry->tworzElement(WEZEL_XML_ROOT)->tworzElement(WEZEL_XML_GRA);
			if (!dokumentGry->zapisz(ustawienia_[ATRYBUT_PLIK_GRY].c_str())){
				return false;
			}
		}

		auto wezel = dokumentGry->pobierzElement(WEZEL_XML_ROOT);
		if (!wezel){
			return false;
		}
		if (wezel && *wezel){
			std::shared_ptr<Gra> gra = instancjaGry_;
			try{
				instancjaGry_ = std::make_shared<Gra>(logger_, *zarzadcaLokacji_, ustawienia_);
				if (root && instancjaGry_->wczytajDane(root)){
					auto gra = wezel->pobierzElement(WEZEL_XML_GRA);
					if (gra){
						auto element = XmlBO::ZnajdzWezel<NOTHROW>(gra, WEZEL_XML_ZARZADCA);
						if (element){
							if (zarzadcaLokacji_->odczytaj(element)){							
								return true;
							}
						}
					}
				}
				instancjaGry_ = gra;
				return false;
			}
			catch (STyp::Wyjatek& e){
#ifndef LOG_OFF_ALL
				logger_.loguj(SLog::Log::Error, e.generujKomunikat());
#endif
			}
			catch (std::exception& e){
#ifndef LOG_OFF_ALL
				logger_.loguj(SLog::Log::Error, e.what());
#endif
			}
			catch (...){
			}
			instancjaGry_ = gra;
		}
		return false;
	}

	bool Aplikacja::przetworzArgumenty(){
		if (!argumenty || iloscArgumentow <= 0)
			return false;

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

		parametryUruchomieniowe_.emplace("-NoConsola", OpcjeParametru(0, [&](std::vector<char*> lista)->bool{
			czyKonsola_ = false;
			return true;
		}));

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
			for (int offset = 1; offset <= parametr->second.iloscParametrow_; ++offset){
				lista.push_back(argumenty[numer + offset]);
			}
			if (parametr->second.funkcja_(lista))
				numer += parametr->second.iloscParametrow_;
			else
				return false;
		}
		return true;
	}

	void Aplikacja::wykonajPolecenie(const std::string& polecenie){
		auto sPolecenie = Utils::trim(polecenie);
		auto iter = std::find_if(sPolecenie.begin(), sPolecenie.end(), [](int i){ return ::isspace(i); });
		std::string nazwa(sPolecenie.begin(), iter);
		sPolecenie.erase(sPolecenie.begin(),iter);
		auto parametry = Utils::trim(sPolecenie);
		if (logger_.czyLogiOdblokowane(SLog::Log::Debug)){
			logger_.loguj(SLog::Log::Debug, "Polecenie: \"" + nazwa + "\" - Parametry: \"" + parametry + "\"");
		}
		if (!nazwa.empty()){
			auto metoda = poleceniaKonsoli_.find(nazwa);
			if (metoda != poleceniaKonsoli_.end()){
				metoda->second(parametry);
			}
		}
	}

	__int64 Aplikacja::pobierzNumerLosowy(){
		return dystrybutor_(generator_);
	}

	std::string Aplikacja::napis() const{
		SLog::Logger logger(NAZWAKLASY(Aplikacja));

		std::stringstream streamCzyZainicjalizowanaBiblioteka_;
		streamCzyZainicjalizowanaBiblioteka_.imbue(std::locale());
		streamCzyZainicjalizowanaBiblioteka_ << std::boolalpha << czyZainicjalizowanaBiblioteka_;
		logger.dodajPole(NAZWAPOLA(czyZainicjalizowanaBiblioteka_), NAZWAKLASY2(czyZainicjalizowanaBiblioteka_), streamCzyZainicjalizowanaBiblioteka_.str());
		logger.dodajPole(NAZWAPOLA(uchwyt_), NAZWAKLASY2(uchwyt_->unused), std::to_string(uchwyt_->unused));

		std::stringstream streamSymInitialize_;
		streamSymInitialize_.imbue(std::locale("C"));
		streamSymInitialize_ << "0x" << std::hex << (unsigned int)(symInitialize_);
		logger.dodajPole(NAZWAPOLA(symInitialize_), NAZWAKLASY2(symInitialize_), streamSymInitialize_.str());

		std::stringstream streamSymFromAddr_;
		streamSymFromAddr_.imbue(std::locale("C"));
		streamSymFromAddr_ << "0x" << std::hex << (unsigned int)(symFromAddr_);
		logger.dodajPole(NAZWAPOLA(symFromAddr_), NAZWAKLASY2(symFromAddr_), streamSymFromAddr_.str());

		logger.dodajPole(NAZWAPOLA(plikKonfiguracyjny_), NAZWAKLASY2(plikKonfiguracyjny_), plikKonfiguracyjny_);
		logger.dodajPole(NAZWAPOLA(ustawienia_), ustawienia_);
		logger.dodajPole(NAZWAPOLA(zarzadcaLokacji_), zarzadcaLokacji_);
		logger.dodajPole(NAZWAPOLA(zarzadcaZasobow_), zarzadcaZasobow_);

		if (instancjaGry_){
			logger.dodajPole(NAZWAPOLA(instancjaGry_), instancjaGry_);
		}
		else{
			logger.dodajPole(NAZWAPOLA(instancjaGry_), NAZWAKLASY2(instancjaGry_), "nullptr");
		}

		if (zarzadcaPluginow_){
			logger.dodajPole(NAZWAPOLA(zarzadcaPluginow_), zarzadcaPluginow_);
		}
		else{
			logger.dodajPole(NAZWAPOLA(zarzadcaPluginow_), NAZWAKLASY2(zarzadcaPluginow_), "nullptr");
		}

		logger.dodajPole(NAZWAPOLA(fabrykator_), fabrykator_);

		logger.dodajPole(NAZWAPOLA(iloscArgumentow), NAZWAKLASY2(iloscArgumentow), std::to_string(iloscArgumentow));

		for (int i = 0; i < iloscArgumentow; ++i){
			if (argumenty[i] != nullptr)
				logger.dodajPole(NAZWAPOLA(argumenty) + std::to_string(i), NAZWAKLASY2(argumenty[i]), argumenty[i]);
			else
				logger.dodajPole(NAZWAPOLA(argumenty) + std::to_string(i), "char*", "nullptr");
		}

		logger.dodajPole(NAZWAPOLA(logger_), logger_);

		return std::move(logger.napis());
	}
};
