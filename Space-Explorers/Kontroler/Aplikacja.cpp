#include "Aplikacja.h"
#include "Gra.h"

#include <io.h>
#include <WinSock2.h>

#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\Utils.h"
#include "Narzedzia\Stale.h"

#include "Widok\Konsola\Konsola.h"

#include "Zarzadca\Fabrykator.h"
#include "Narzedzia\ZarzadcaZasobow.h"
#include "Zarzadca\ZarzadcaPluginow.h"
#include "Zarzadca\ZarzadcaUzytkownikow.h"
#include "Zarzadca\ZarzadcaLokacji.h"

#include "MaszynaStanow\MaszynaStanow.h"

#include "Parser\ParserDokumentXml.h"
#include "Eksport\IProxyBO.h"

#include "Kontroler\Wielowatkowosc\ObserwatorWatkow.h"

namespace SpEx{

	int Aplikacja::iloscArgumentow = 0;
	char** Aplikacja::argumenty = nullptr;

	void Aplikacja::nowaGra(){
		instancjaGry_ = std::make_shared<Gra>(logger_, *zarzadcaLokacji_, ustawienia_);
	}
	
	__int64 Aplikacja::pobierzNumerLosowy(){
		return dystrybutor_(generator_);
	}
	
	std::string Aplikacja::pobierzDebugInfo() const{
#if !(defined(LOG_OFF_ALL) || defined(LOG_OFF_DEBUG))
		return std::move(Aplikacja::napis() + " " +  MaszynaStanow::pobierzInstancje().napis());
#else
		return std::string();
#endif
	}

	void Aplikacja::start(){
		if (proxy_){

			if(konsola_)
				proxy_->rejestrujMetodyKonsoli();

			SpEx::MaszynaStanow::pobierzInstancje().inicjalizuj(); 
						
			switch (proxy_->pobierzTrybAplikacji())
			{
			case TrybAplikacji::Serwer:
				logger_.loguj(SLog::Log::Info, "Tryb dzia�ania aplikacji: Serwer");
				SpEx::MaszynaStanow::pobierzInstancje().start();
				break;
			case TrybAplikacji::Klient:
				logger_.loguj(SLog::Log::Info, "Tryb dzia�ania aplikacji: Klient");
				SpEx::MaszynaStanow::pobierzInstancje().start();
				break;
			case TrybAplikacji::Invalid:
				logger_.loguj(SLog::Log::Info, "Tryb dzia�ania aplikacji: Invalid");
				SpEx::MaszynaStanow::pobierzInstancje().wyczysc();
				break;
			default:
				break;
			}
		}
	}
		
	bool Aplikacja::wczytajGre(std::shared_ptr<SPar::ParserElement> root){
		auto dokumentGry = std::make_shared<SPar::ParserDokumentXml>();
		std::string plikGry;
		if (!ustawienia_[ATRYBUT_PLIK_GRY].empty())
			plikGry += ustawienia_[ATRYBUT_GLOWNY_FOLDER_GRY] + "\\";
		plikGry += ustawienia_[ATRYBUT_PLIK_GRY];
		if (!dokumentGry->odczytaj(plikGry.c_str())){
			Utils::generujSzablonPlikuGry(std::static_pointer_cast<SPar::ParserDokument>(dokumentGry));
			if (!dokumentGry->zapisz(plikGry.c_str())){
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
		bool retVal = false;
		std::string plikGry;
		if (!ustawienia_[ATRYBUT_PLIK_GRY].empty())
			plikGry += ustawienia_[ATRYBUT_GLOWNY_FOLDER_GRY] + "\\";
		plikGry += ustawienia_[ATRYBUT_PLIK_GRY];
		try{
			auto dokumentGry = std::make_shared<SPar::ParserDokumentXml>();
			auto wezel = dokumentGry->tworzElement(WEZEL_XML_ROOT);
			if (wezel) {
				if (instancjaGry_)
					instancjaGry_->zapiszGracza();

				zarzadcaUzytkownikow_->zapiszDane();

				if (zarzadcaLokacji_->zapisz(wezel->tworzElement(WEZEL_XML_GRA)))
					retVal = dokumentGry->zapisz(plikGry.c_str());
			}			
		}
		catch (...){
			std::locale::global(std::locale(ustawienia_[ATRYBUT_JEZYK_APLIKACJI]));
			throw;
		}
		std::locale::global(std::locale(ustawienia_[ATRYBUT_JEZYK_APLIKACJI]));
		return retVal;
	}

	Aplikacja::~Aplikacja()
	{
		if (konsola_){
			konsola_->zakoncz();
			konsola_->czekajNaZakonczenie();
		}

		SpEx::ObserwatorWatkow::pobierzInstancje().wylaczJakPuste();
		SpEx::ObserwatorWatkow::pobierzInstancje().czekajNaZakonczenie();

		WSACleanup();
	}

	std::string Aplikacja::napis() const{
		SLog::Logger logger(NAZWAKLASY(Aplikacja));

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
