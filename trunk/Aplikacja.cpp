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

void myPurecallHandler(){
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, SpEx::Aplikacja::pobierzInstancje().pobierzSladStosu());
}

void myInvalidParameterHandler(const wchar_t* expression,
	const wchar_t* function,
	const wchar_t* file,
	unsigned int line,
	uintptr_t pReserved)
{
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
}

namespace SpEx{

	int Aplikacja::iloscArgumentow = 0;
	char** Aplikacja::argumenty = nullptr;

	Aplikacja::Aplikacja()
		: czyZainicjalizowanaBiblioteka_(false), logger_(SLog::Log::pobierzInstancje()), instancjaGry_(nullptr)
	{
		/* ------- Wstêpna konfiguracja logów ------- */
#ifdef TESTS
		/* Wylaczenie logow typu debug na potrzeby ograniczenia logow testow*/
		logger_.zablokujLogi(SLog::Log::Debug);
		/* ------------------------------------ */
#endif
		logger_.dodajGniazdoWyjsciowe([](SLog::Log::TypLogow typ, const std::string& komunikat)->void{ std::cout << komunikat; });
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
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), STyp::Identyfikator(),
				STyp::Tekst("B³¹d inicjalizacji argumentów"),
				STyp::Tekst("Podczas inicjalizacji argumentów wyst¹pi³ b³¹d."));
		}

		if (!ustawienia_.zaladuj(plikKonfiguracyjny_)){
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), STyp::Identyfikator(),
				STyp::Tekst("B³¹d inicjalizacji argumentów"),
				STyp::Tekst("Nie powiod³o siê wczytywanie pliku konfiguracyjnego: " + plikKonfiguracyjny_ ));
		}
		logger_.ustawFormatCzasu(ustawienia_.pobierzFormatDatyLogow());
		
		for (auto typ : ustawienia_.pobierzOdblokowaneLogi()){
			logger_.odblokujLogi(typ);
		}

		for (auto typ : ustawienia_.pobierzZablokowaneLogi()){
			logger_.zablokujLogi(typ);
		}

		struct tm timeinfo;
		time_t t = time(nullptr);
		localtime_s(&timeinfo, &t);
		char s[20];
		if (strftime(s, 20, ustawienia_.pobierzFormatDatyPlikuLogow().c_str(), &timeinfo) == 0){
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), STyp::Identyfikator(),
				STyp::Tekst("B³¹d inicjalizacji argumentów"),
				STyp::Tekst("Nie poprawny format daty u¿ytej w nazwie pliku logów."));
		}
		std::stringstream sfile;
		sfile << ustawienia_.pobierzPrzedrostekPlikuLogow() << s << ".log";
		std::string filename = sfile.str();
		logger_.dodajGniazdoWyjsciowe([&filename](SLog::Log::TypLogow typ, const std::string& komunikat)->void{ static std::fstream plik(filename, std::ios_base::app); plik << komunikat; });
		/* ------------------------------------ */
		

		logger_.loguj(SLog::Log::Info, "Start aplikacji Space-Explorers.");

		//Wyswietlanie informacji o aplikacji
		logApInfo();

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

		zarzadca_.zaladujPliki();

		if (!zaladujOpcje()){
			throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), STyp::Identyfikator(),
				STyp::Tekst("B³¹d przetwarzania pliku z opcjami"),
				STyp::Tekst("Podczas przetwa¿ania pliku z opcjami wyst¹pi³ b³¹d."));
		}

		pluginy_ = std::make_shared<SPlu::Cplugin>(ustawienia_.pobierzFolderPlugin(), SZmi::ZmianaFabryka::pobierzInstancje(), logger_);

		if (!RejestrujZmianaPoziomObiektu(SZmi::ZmianaFabryka::pobierzInstancje(), logger_))
			throw STyp::Wyjatek(EXCEPTION_PLACE, pobierzSladStosu(), STyp::Identyfikator(),
			STyp::Tekst("B³ad rejestracji zmiany."),
			STyp::Tekst("Nie powiod³a siê rejestracja zmiany sparawdzaj¹cej poziom obiektu."));

		if (!pluginy_->zaladujDomyslneKlasyZmian())
			throw STyp::Wyjatek(EXCEPTION_PLACE, pobierzSladStosu(), STyp::Identyfikator(),
			STyp::Tekst("B³ad rejestracji zmiany."),
			STyp::Tekst("Nie powiod³a siê rejestracja domyœlnych obiektów zmiany."));

		if (!pluginy_->zaladujZewnetrzneKlasyZmian())
			throw STyp::Wyjatek(EXCEPTION_PLACE, pobierzSladStosu(), STyp::Identyfikator(),
			STyp::Tekst("B³ad rejestracji zmiany."),
			STyp::Tekst("Nie powiod³a siê rejestracja dodatkowych obiektów zmiany."));

		_set_purecall_handler(myPurecallHandler);
		_set_invalid_parameter_handler(myInvalidParameterHandler);

		instancjaGry_ = std::make_shared<Gra>(*this, SZmi::ZmianaFabryka::pobierzInstancje());
	}

	SLog::Log& Aplikacja::pobierzLogger() const{
		return logger_;
	}

	Gra& Aplikacja::pobierzGre() const{
		return *instancjaGry_;
	}

	bool Aplikacja::wczytajDane(std::shared_ptr<SPar::ParserElement> root){
		return instancjaGry_->wczytajDane(root);
	}

	void Aplikacja::wyczyscDane(){
		instancjaGry_ = std::make_shared<Gra>(*this, SZmi::ZmianaFabryka::pobierzInstancje());
	}

	bool Aplikacja::zaladujOpcje(){
		try{
			std::locale pl(ustawienia_.pobierzJezykAplikacji());
			std::locale::global(pl);
			this->logger_.loguj(SLog::Log::Debug, std::string("Separator u³amka: ") + std::use_facet<std::numpunct<char>>(pl).decimal_point());

			auto nazwaPlikuDanych_ = ustawienia_.pobierzPlikDanych();
			if (_access(nazwaPlikuDanych_.c_str(), 0) == -1){ // Sprawdzenie czy folder istnieje
				throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), STyp::Identyfikator(), STyp::Tekst("Brak pliku danych."), STyp::Tekst("Plik : " + nazwaPlikuDanych_ +  " z danymi programu nie zosta³ znaleziony!"));
			}

			auto folderPluginow_ = ustawienia_.pobierzFolderPlugin();
			if (_access(folderPluginow_.c_str(), 0) == -1){ // Sprawdzenie czy folder istnieje
				throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(pobierzSladStosu()), STyp::Identyfikator(), STyp::Tekst("Brak folderu plugin."), STyp::Tekst("Folder :" + folderPluginow_ + " nie zosta³ znaleziony!"));
			}
		}
		catch (std::exception &e){
			logger_.loguj(SLog::Log::Error, e.what());
			return false;
		}
		return true;
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
		if (uchwyt_)
			FreeLibrary(uchwyt_);
	}

	bool Aplikacja::zapiszGre(const std::string& nazwa, const std::string& hash){

		auto wezel = zarzadca_.tworzWezelGry();
		std::locale::global(std::locale("C"));
		try{
			if (instancjaGry_->zapisz(wezel) && instancjaGry_->zapisz(nazwa, hash)){
				std::locale::global(std::locale(ustawienia_.pobierzJezykAplikacji()));
				return zarzadca_.zapiszWezelGry();
			}
		}
		catch (...){
			std::locale::global(std::locale(ustawienia_.pobierzJezykAplikacji()));
			throw;
		}
		std::locale::global(std::locale(ustawienia_.pobierzJezykAplikacji()));
		return false;
	}

	bool Aplikacja::wczytajGre(std::shared_ptr<SPar::ParserElement> root, const std::string& nazwa, const std::string& hash){
		auto wezel = zarzadca_.otworzWezelGry();
		if (wezel && *wezel){
			std::shared_ptr<Gra> gra = instancjaGry_;
			try{
				instancjaGry_ = std::make_shared<Gra>(*this, SZmi::ZmianaFabryka::pobierzInstancje());
				Walidator::pobierzInstancje().wyczysc();
				Walidator::pobierzInstancje().dodajNowyIdentyfikatorPlanety(STyp::Identyfikator(0x0)); // Poprawna wartoœæ; U¿ywana gdy obiekty znajduj¹ siê we flocie.
				if (root && instancjaGry_->wczytajDane(root)){
					if (instancjaGry_->odczytaj(wezel->pobierzElement(WEZEL_XML_GRA)))
					if (instancjaGry_->odczytaj(nazwa, hash))
					if (Walidator::pobierzInstancje().waliduj())
						return true;
				}
				instancjaGry_ = gra;
				return false;
			}
			catch (std::exception& e){
				logger_.loguj(SLog::Log::Error, e.what());
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
