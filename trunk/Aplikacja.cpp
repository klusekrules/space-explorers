#include "Aplikacja.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <io.h>
#include "ZmianaPoziomObiektu.h"
#include "DefinicjeWezlowXML.h"
#include "Walidator.h"
#include "TGUI\TGUI.hpp"
#include "ListaObiektowGui.h"
#include "ListaSurowcowGui.h"
#include "LogListGui.h"
#include "BladKonfiguracjiAplikacji.h"
#include "LuaState.h"
#include "DllModule.h"

#define KOMUNIKAT_BLAD_PRZETWARZANIA_ARGUMENTU STyp::Tekst("Podczas przetwarzabua argumentów wyst¹pi³ b³¹d.")
#define KOMUNIKAT_BLAD_PLIKU_KONFIGURACYJNEGO(plik) STyp::Tekst("Nie powiod³o siê wczytywanie pliku konfiguracyjnego: " + plik)
#define KOMUNIKAT_BLAD_FORMATU_DATY STyp::Tekst("Nie poprawny format daty u¿ytej w nazwie pliku logów.")
#define KOMUNIKAT_BLAD_LADOWANIA_OPCJI STyp::Tekst("Podczas przetwa¿ania pliku z opcjami wyst¹pi³ b³¹d.")
#define KOMUNIKAT_BLAD_REJESTRACJI_ZMIANY_POZIOMU STyp::Tekst("Nie powiod³a siê rejestracja zmiany sparawdzaj¹cej poziom obiektu.")
#define KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DOMYSLNYCH STyp::Tekst("Nie powiod³a siê rejestracja domyœlnych obiektów zmiany.")
#define KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DODATKOWYCH STyp::Tekst("Nie powiod³a siê rejestracja dodatkowych obiektów zmiany.")
#define KOMUNIKAT_BLAD_BRAK_PLIKU_DANYCH(plik) STyp::Tekst("Plik : " + plik + " z danymi programu nie zosta³ znaleziony!")
#define KOMUNIKAT_BLAD_BRAK_FOLDERU_PLUGINOW(folder) STyp::Tekst("Folder :" + folder + " nie zosta³ znaleziony!")

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
		: czyZainicjalizowanaBiblioteka_(false), logger_(SLog::Log::pobierzInstancje()), fabrykator_(), instancjaGry_(nullptr)
	{
		tgui::TGUI_WidgetFactory.RejestrujKreatorWidzetu("listasurowcowgui", tgui::ListaSurowcowGui::createWidget);
		tgui::TGUI_WidgetFactory.RejestrujKreatorWidzetu("listaobiektowgui", tgui::ListaObiektowGui::createWidget);
		tgui::TGUI_WidgetFactory.RejestrujKreatorWidzetu("kontrolkaobiektu", tgui::KontrolkaObiektu::createWidget);
		tgui::TGUI_WidgetFactory.RejestrujKreatorWidzetu("loglistgui", tgui::LogListGui::createWidget);
		LuaState::Rejestruj(zarzadcaZasobow_);
		DllModule::Rejestruj(zarzadcaZasobow_);

		/* ------- Wstêpna konfiguracja logów ------- */
		logger_.dodajGniazdoWyjsciowe([](SLog::Log::TypLogow typ, const std::string& czas, const std::string& komunikat)->void{ 
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
			std::cout << czas << sTyp << komunikat;
		});
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
		logger_.ustawFormatCzasu(ustawienia_.pobierzFormatDatyLogow());
		
		for (auto typ : ustawienia_.pobierzOdblokowaneLogi()){
			logger_.odblokujLogi(typ);
		}

		for (auto typ : ustawienia_.pobierzZablokowaneLogi()){
			logger_.zablokujLogi(typ);
		}

		if (!zaladujOpcje()){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_LADOWANIA_OPCJI);
		}

		struct tm timeinfo;
		time_t t = time(nullptr);
		localtime_s(&timeinfo, &t);
		char s[20];
		if (strftime(s, 20, ustawienia_.pobierzFormatDatyPlikuLogow().c_str(), &timeinfo) == 0){
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_FORMATU_DATY);
		}
		std::stringstream sfile;
		sfile << ustawienia_.pobierzPrzedrostekPlikuLogow() << s << ".log";
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
			plik << czas << sTyp << komunikat;
		});
		/* ------------------------------------ */
#ifndef LOG_OFF_ALL
		logger_.loguj(SLog::Log::Info, "Start aplikacji Space-Explorers.");
#endif
		//Wyswietlanie informacji o aplikacji
		logApInfo();
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
		zarzadcaPamieci_.zaladujPliki(ustawienia_, std::bind(&Aplikacja::pobierzSladStosu, this));
		zarzadcaLokacji_.zaladujUstawienia(ustawienia_, std::bind(&Aplikacja::pobierzSladStosu, this));
		zarzadcaZasobow_.inicjalizuj(zarzadcaPamieci_.pobierzWezelPowiazanZasobow());

		pluginy_ = std::make_shared<SPlu::Cplugin>(ustawienia_.pobierzFolderPlugin(), fabrykator_.pobierzFabrykeZmian(), logger_);

		if (!RejestrujZmianaPoziomObiektu(fabrykator_.pobierzFabrykeZmian(), logger_))
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIANY_POZIOMU);

		if (!pluginy_->zaladujDomyslneKlasyZmian())
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DOMYSLNYCH);

		if (!pluginy_->zaladujZewnetrzneKlasyZmian())
			throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_REJESTRACJI_ZMIAN_DODATKOWYCH);

		_set_purecall_handler(myPurecallHandler);
		_set_invalid_parameter_handler(myInvalidParameterHandler);

		instancjaGry_ = std::make_shared<Gra>(logger_, zarzadcaLokacji_, zarzadcaPamieci_);
	}

	void Aplikacja::wyczyscDane(){
		instancjaGry_ = std::make_shared<Gra>(logger_, zarzadcaLokacji_, zarzadcaPamieci_);
	}

	bool Aplikacja::zaladujOpcje(){
		try{
			std::locale pl(ustawienia_.pobierzJezykAplikacji());
			std::locale::global(pl);
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
			logger_.loguj(SLog::Log::Debug, std::string("Separator u³amka: ") + std::use_facet<std::numpunct<char>>(pl).decimal_point());
#endif
			auto nazwaPlikuDanych_ = ustawienia_.pobierzPlikDanych();
			if (_access(nazwaPlikuDanych_.c_str(), 0) == -1){ // Sprawdzenie czy folder istnieje
				throw BladKonfiguracjiAplikacji(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), pobierzDebugInfo(), KOMUNIKAT_BLAD_BRAK_PLIKU_DANYCH(nazwaPlikuDanych_));
			}

			auto folderPluginow_ = ustawienia_.pobierzFolderPlugin();
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
		std::string str;
		SLog::Logger logger(NAZWAKLASY(Aplikacja));
		logger.dodajPole(NAZWAPOLA(czyZainicjalizowanaBiblioteka_), NAZWAKLASY2(czyZainicjalizowanaBiblioteka_), std::to_string(czyZainicjalizowanaBiblioteka_));
		logger.dodajPole(NAZWAPOLA(uchwyt_), NAZWAKLASY2(uchwyt_->unused), std::to_string(uchwyt_->unused));
		logger.dodajPole(NAZWAPOLA(symInitialize_), NAZWAKLASY2(symInitialize_), std::to_string((unsigned int)symInitialize_));
		logger.dodajPole(NAZWAPOLA(symFromAddr_), NAZWAKLASY2(symFromAddr_), std::to_string((unsigned int)symFromAddr_));
		logger.dodajPole(NAZWAPOLA(plikKonfiguracyjny_), NAZWAKLASY2(plikKonfiguracyjny_), plikKonfiguracyjny_);
		logger.dodajPole(NAZWAPOLA(ustawienia_), ustawienia_);
		logger.dodajPole(NAZWAPOLA(zarzadcaLokacji_), zarzadcaLokacji_);
		logger.dodajPole(NAZWAPOLA(zarzadcaZasobow_), zarzadcaZasobow_);
		return str;
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
		logger_.loguj(SLog::Log::Info,zarzadcaZasobow_);
		if (uchwyt_)
			FreeLibrary(uchwyt_);
	}

	bool Aplikacja::zapiszGre(const std::string& nazwa, const std::string& hash){
		std::locale::global(std::locale("C"));
		try{
			auto wezel = zarzadcaPamieci_.tworzWezelGry();
			if (zarzadcaLokacji_.zapisz(wezel->tworzElement(WEZEL_XML_GRA)) && instancjaGry_->zapisz(nazwa, hash)){
				std::locale::global(std::locale(ustawienia_.pobierzJezykAplikacji()));
				return zarzadcaPamieci_.zapiszWezelGry();
			}
		}
		catch (...){
			std::locale::global(std::locale(ustawienia_.pobierzJezykAplikacji()));
			throw;
		}
		std::locale::global(std::locale(ustawienia_.pobierzJezykAplikacji()));
		return false;
	}

	bool Aplikacja::wczytajGre(std::shared_ptr<SPar::ParserElement> root){
		auto wezel = zarzadcaPamieci_.otworzWezelGry();
		if (wezel && *wezel){
			std::shared_ptr<Gra> gra = instancjaGry_;
			try{
				instancjaGry_ = std::make_shared<Gra>(logger_, zarzadcaLokacji_, zarzadcaPamieci_);
				Walidator::pobierzInstancje().wyczysc();
				Walidator::pobierzInstancje().dodajNowyIdentyfikatorPlanety(STyp::Identyfikator(0x0)); // Poprawna wartoœæ; U¿ywana gdy obiekty znajduj¹ siê we flocie.
				if (root && instancjaGry_->wczytajDane(root)){
					auto gra = wezel->pobierzElement(WEZEL_XML_GRA);
					if (gra){
						auto element = XmlBO::ZnajdzWezel<NOTHROW>(gra, WEZEL_XML_ZARZADCA);
						if (element){
							if (zarzadcaLokacji_.odczytaj(element)){
								if (Walidator::pobierzInstancje().waliduj()){
									return true;
								}
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
		plikKonfiguracyjny_ = "options.xml";
		for (int numer = 0; numer < iloscArgumentow; ++numer){
			if (!argumenty[numer])
				continue;
			std::string argument(argumenty[numer]);
			if (argument.empty())
				continue;
			if (!argument.compare("-O")){
				++numer;
				if (numer >= iloscArgumentow || !argumenty[numer])
					return false;
				std::string nazwa(argumenty[numer]);
				if (nazwa.empty())
					return false;
				plikKonfiguracyjny_ = nazwa;
			}
		}
		return true;
	}
};
