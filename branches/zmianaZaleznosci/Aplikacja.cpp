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
#include "Parser\ParserDokumentXml.h"

void myPurecallHandler(){
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error,SpEx::Aplikacja::pobierzInstancje().pobierzSladStosu());
}

void myInvalidParameterHandler(const wchar_t* expression,
							   const wchar_t* function, 
							   const wchar_t* file, 
							   unsigned int line, 
							   uintptr_t pReserved)
{
	char* c_expression = new char[wcslen(expression)+1];
	char* c_function = new char[wcslen(function)+1];
	char* c_file = new char[wcslen(file)+1];
	wcstombs_s(nullptr,c_expression,wcslen(expression)+1,expression,wcslen(expression));	
	wcstombs_s(nullptr,c_function,wcslen(function)+1,function,wcslen(function));
	wcstombs_s(nullptr,c_file,wcslen(file)+1,file,wcslen(file));
	std::stringstream str;
	str<<"Invalid parameter detected in function: "<<c_function<<". File: " << c_file <<". Line: "<<line<<".\nExpression: "<< c_expression;
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, str.str());
	SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, SpEx::Aplikacja::pobierzInstancje().pobierzSladStosu());
}

namespace SpEx{

	int Aplikacja::iloscArgumentow = 0;
	char** Aplikacja::argumenty = nullptr;

	Aplikacja& Aplikacja::pobierzInstancje(){
		static Aplikacja instancja;
		return instancja;
	}

	Aplikacja::Aplikacja() throw(NiezainicjalizowanaKlasa)
		: czyZainicjalizowanaBiblioteka_(false), logger_(SLog::Log::pobierzInstancje()), instancjaGry_(new Gra(*this))
	{

#ifdef TESTS
		/* Wylaczenie logow typu debug na potrzeby ograniczenia logow testow*/
		logger_.zablokujLogi(SLog::Log::Debug);
		/* ------------------------------------ */
#endif

		//Ladowanie potrzebnych bibliotek
		uchwyt_ = LoadLibrary("Dbghelp.dll");
		if (uchwyt_){
			symInitialize_ = (SymInitializeS)GetProcAddress(uchwyt_, "SymInitialize");
			symFromAddr_ = (SymFromAddrS)GetProcAddress(uchwyt_, "SymFromAddr");
			if (symFromAddr_ && symInitialize_){
				czyZainicjalizowanaBiblioteka_ = true;
			}
		}

		/* ------- Konfiguracja parametr�w programu -------*/
		if (!przetworzArgumenty()){
			throw STyp::Wyjatek(EXCEPTION_PLACE,STyp::Tekst());
		}

		/* ------- Konfiguracja Loggera -------*/
		struct tm timeinfo;
		time_t t = time(nullptr);
		localtime_s(&timeinfo, &t);
		char s[20];
		strftime(s, 20, "%Y-%m-%d", &timeinfo);
		std::stringstream sfile;
		sfile << "space-explorers-" << s << ".log";
		std::string filename = sfile.str();
		logger_.ustawFormatCzasu(SLog::Log::Czas);
		logger_.dodajGniazdoWyjsciowe([](SLog::Log::TypLogow typ, const std::string& komunikat)->void{ std::cout << komunikat; });
		logger_.dodajGniazdoWyjsciowe([&filename](SLog::Log::TypLogow typ, const std::string& komunikat)->void{ static std::fstream plik(filename, std::ios_base::app); plik << komunikat; });
		/* ------------------------------------ */

		if (!zaladujOpcje()){
			throw STyp::Wyjatek(EXCEPTION_PLACE,STyp::Tekst());
		}

		//Wyswietlanie informacji o aplikacji
		logApInfo();

		//Wyswietlanie informacji o zaladowanej bibliotece
		if (uchwyt_){
			if (czyZainicjalizowanaBiblioteka_){
				logger_.loguj(SLog::Log::Info, "Za�adowano biblioteke Dbghelp.dll");
			}
			else{
				logger_.loguj(SLog::Log::Warning, "Nie zanaleziono funkcji SymInitialize i/lub SymFromAddr.");
			}
		}
		else{
			logger_.loguj(SLog::Log::Warning, "Nie za�adowano biblioteki Dbghelp.dll");
		}

		pluginy_ = std::shared_ptr<SPlu::Cplugin>(new SPlu::Cplugin(folderPluginow_, instancjaGry_->pobierzFabrykeZmian(), logger_));

		RejestrujZmianaPoziomObiektu(instancjaGry_->pobierzFabrykeZmian(), logger_);

		if (!pluginy_->zaladujDomyslneKlasyZmian())
			throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE, STyp::Tekst("Domyslne elementy zmiany."));

		if (!pluginy_->zaladujZewnetrzneKlasyZmian())
			throw NiezainicjalizowanaKlasa(EXCEPTION_PLACE, STyp::Tekst("Dodatkowe elementy zmiany."));


		_set_purecall_handler(myPurecallHandler);
		_set_invalid_parameter_handler(myInvalidParameterHandler);

	}

	Aplikacja::Aplikacja(const Aplikacja& aplikacja)
		:logger_(SLog::Log::pobierzInstancje())
	{
	}

	Aplikacja& Aplikacja::operator=(const Aplikacja& aplikacja){
		return *this;
	}

	SLog::Log& Aplikacja::pobierzLogger() const{
		return logger_;
	}

	Gra& Aplikacja::pobierzGre() const{
		return *instancjaGry_;
	}

	bool Aplikacja::wczytajDane(){
		return instancjaGry_->wczytajDane(nazwaPlikuDanych_);
	}

	void Aplikacja::wyczyscDane(){
		instancjaGry_ = std::shared_ptr<Gra>(new Gra(*this));
	}

	bool Aplikacja::zaladujOpcje(){
		SPar::ParserDokumentXml dane;
		try{
			dane.odczytaj(nazwaPlikuOpcji_.c_str());
			auto root_data = dane.pobierzElement("SpaceGame");
			if (root_data){

				auto jezyk = XmlBO::ZnajdzWezel<NOTHROW>(root_data, "locale");
				if (jezyk){
					jezykAplikacji_ = jezyk->pobierzTekst();
					if (jezykAplikacji_.size() != 0){
						try{
							std::locale pl(jezykAplikacji_);
							std::locale::global(pl);
							this->logger_.loguj(SLog::Log::Debug, std::string("Separator u�amka: ") + std::use_facet<std::numpunct<char>>(pl).decimal_point());
						}
						catch (std::exception&){
							jezykAplikacji_.clear();
						}
					}
				}

				if (jezykAplikacji_.size() == 0){
					jezykAplikacji_ = "Polish";
					std::locale pl(jezykAplikacji_);
					std::locale::global(pl);
				}

				auto plikDanych = XmlBO::ZnajdzWezel<THROW>(root_data, "data");
				if (plikDanych){
					nazwaPlikuDanych_ = plikDanych->pobierzTekst();
					if (_access(nazwaPlikuDanych_.c_str(), 0) == -1){ // Sprawdzenie czy folder istnieje
						throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(), STyp::Identyfikator(), STyp::Tekst("Brak pliku danych."), STyp::Tekst("Plik z danymi programu nie zosta� znaleziony!"));
					}
				}
				else{
					throw WyjatekParseraXML(EXCEPTION_PLACE, std::exception(""), WyjatekParseraXML::trescBladStrukturyXml);
				}

				auto pluginy = XmlBO::ZnajdzWezel<NOTHROW>(root_data, "plugins");
				if (pluginy){
					folderPluginow_ = pluginy->pobierzTekst();
					if (_access(folderPluginow_.c_str(), 0) == -1){ // Sprawdzenie czy folder istnieje
						folderPluginow_.clear();
					}
				}

				if (folderPluginow_.size() == 0){
					folderPluginow_ = "plugins\\";
				}

			}
			else{
				throw WyjatekParseraXML(EXCEPTION_PLACE, std::exception(""), WyjatekParseraXML::trescBladStrukturyXml);
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
				// i = 1 - Pomini�cie wywo�ania funkcji getStackTrace
				// i = 0 - W��cznie do wy�wietlanego wyniku wywo�ania funkcji getStackTrace
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

	bool Aplikacja::zapiszGre(const std::string& nazwa, const std::string& hash) const{
		SPar::ParserDokumentXml dokument;
		auto wezel = dokument.tworzElement(WEZEL_XML_ROOT);
		std::locale::global(std::locale("C"));
		if (instancjaGry_->zapisz(wezel) && instancjaGry_->zapisz(nazwa, hash)){
			std::locale::global(std::locale(jezykAplikacji_));
			return dokument.zapisz("save\\gra.xml") == tinyxml2::XML_NO_ERROR;
		}
		std::locale::global(std::locale(jezykAplikacji_));
		return false;
	}

	bool Aplikacja::wczytajGre(const std::string& nazwa, const std::string& hash){
		SPar::ParserDokumentXml dokument;
		if (dokument.odczytaj("save\\gra.xml") != tinyxml2::XML_NO_ERROR){
			auto wezel = dokument.tworzElement(WEZEL_XML_ROOT);
			auto gra = dokument.tworzElement(WEZEL_XML_GRA);
			dokument.zapisz("save\\gra.xml");
		}
		auto wezel = dokument.pobierzElement(nullptr);
		if (wezel){
			std::shared_ptr<Gra> gra = instancjaGry_;
			try{
				instancjaGry_ = std::shared_ptr<Gra>(new Gra(*this));
				Walidator::pobierzInstancje().wyczysc();
				Walidator::pobierzInstancje().dodajNowyIdentyfikatorPlanety(STyp::Identyfikator(0x0)); // Poprawna warto��; U�ywana gdy obiekty znajduj� si� we flocie.
				if (instancjaGry_->wczytajDane(this->nazwaPlikuDanych_)){
					if (instancjaGry_->odczytaj(wezel->pobierzElement(WEZEL_XML_GRA)))
					if (instancjaGry_->odczytaj(nazwa, hash))
					if (Walidator::pobierzInstancje().waliduj())
						return true;
				}
				instancjaGry_ = gra;
				return false;
			}
			catch (STyp::Wyjatek& e){
				logger_.loguj(SLog::Log::Error, e);
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
		nazwaPlikuOpcji_ = "options.xml";
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
				nazwaPlikuOpcji_ = nazwa;
			}
		}
		return true;
	}
}
