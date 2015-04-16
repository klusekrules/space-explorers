#include "Aplikacja.h"
#include "Gra.h"

#include <iomanip>
#include <io.h>
#include <WinSock2.h>

#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\Utils.h"
#include "Utils\StaleUstawienAplikacji.h"

#include "Widok\Konsola\Konsola.h"

#include "Zarzadca\Fabrykator.h"
#include "Zarzadca\ZarzadcaZasobow.h"
#include "Zarzadca\ZarzadcaPluginow.h"
#include "Zarzadca\ZarzadcaUzytkownikow.h"
#include "Zarzadca\ZarzadcaLokacji.h"

#include "MaszynaStanow\MaszynaStanow.h"

#include "Parser\ParserDokumentXml.h"

namespace SpEx{

	int Aplikacja::iloscArgumentow = 0;
	char** Aplikacja::argumenty = nullptr;

	void Aplikacja::nowaGra(){
		instancjaGry_ = std::make_shared<Gra>(logger_, *zarzadcaLokacji_, ustawienia_);
	}
	
	TrybAplikacji Aplikacja::pobierzTrybAplikacji() const{
		return tryb_;
	}

	__int64 Aplikacja::pobierzNumerLosowy(){
		return dystrybutor_(generator_);
	}

	void Aplikacja::logujListePolecenKonsoli() const{
		if(poleceniaKonsoli_.empty()){
			logger_.loguj(SLog::Log::Info,"Brak polecen konsoli.");
		} else{

			logger_.loguj(SLog::Log::Info, "Lista dostêpnych poleceñ konsoli:");
			for (auto & wpis : poleceniaKonsoli_){
				logger_.loguj(SLog::Log::Info, wpis.first + " - " + wpis.second.opisPolecenia_);			
			}
		}
	}
	
	std::string Aplikacja::pobierzDebugInfo() const{
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
		return std::move(Aplikacja::napis() + " " +  MaszynaStanow::pobierzInstancje().napis());
#else
		return std::string();
#endif
	}

	void Aplikacja::wykonajPolecenie(const std::string& polecenie){
		auto sPolecenie = Utils::trim(polecenie);
		auto iter = std::find_if(sPolecenie.begin(), sPolecenie.end(), [](int i){ return ::isspace(i); });
		std::string nazwa(sPolecenie.begin(), iter);
		sPolecenie.erase(sPolecenie.begin(), iter);
		auto parametry = Utils::trim(sPolecenie);
		if (logger_.czyLogiOdblokowane(SLog::Log::Debug)){
			logger_.loguj(SLog::Log::Debug, "Polecenie: \"" + nazwa + "\" - Parametry: \"" + parametry + "\"");
		}
		if (!nazwa.empty()){
			auto metoda = poleceniaKonsoli_.find(nazwa);
			if (metoda != poleceniaKonsoli_.end()){
				metoda->second.funkcja_(parametry);
			}
		}
	}

	void Aplikacja::start(){
		SpEx::MaszynaStanow::pobierzInstancje().inicjalizuj();

		switch (tryb_)
		{
		case TrybAplikacji::Serwer:
			logger_.loguj(SLog::Log::Info, "Tryb dzia³ania aplikacji: Serwer");
			SpEx::MaszynaStanow::pobierzInstancje().start();
			break;
		case TrybAplikacji::Klient:
			logger_.loguj(SLog::Log::Info, "Tryb dzia³ania aplikacji: Klient");
			SpEx::MaszynaStanow::pobierzInstancje().start();
			break;
		case TrybAplikacji::Invalid:
			logger_.loguj(SLog::Log::Info, "Tryb dzia³ania aplikacji: Invalid");
			break;
		default:
			break;
		}
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
				nowaGra();
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
			symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
			symbol->MaxNameLen = 255;
			symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
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
