#include "Gra.h"
#include "DefinicjeWezlowXML.h"
#include <iostream>
#include <fstream>
#include "Walidator.h"
#include "Parser\ParserDokumentXml.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"

#define ATRYBUT_FOLDER_PLIKU_UZYTKOWNIKA "folderPlikowUzytkownikow"

namespace SpEx{

	Gra::Gra(SLog::Log& logger, ZarzadcaLokacji& zarzadcaLokacji, UstawieniaAplikacji& ustawieniaAplikacji)
		: logger_(logger), zarzadcaLokacji_(zarzadcaLokacji), uzytkownik_(nullptr)
	{
		zarzadcaLokacji_.wyczyscDane();
	}

	bool Gra::przeniesPlaneteDoUzytkownika(const STyp::Identyfikator& identyfikator){
		auto planeta = zarzadcaLokacji_.pobierzIZarezerwujPlanete(identyfikator);
		if (!planeta)
			return false;
		if (!uzytkownik_->dodajPlanete(planeta)){
			zarzadcaLokacji_.anulujRezerwacjePlanety(identyfikator);
			return false;
		}
		return true;
	}

	bool Gra::przeniesPlaneteDoUzytkownika(){
		auto planeta = zarzadcaLokacji_.pobierzIZarezerwujPlanete();
		if (!planeta)
			return false;
		if (!uzytkownik_->dodajPlanete(planeta)){
			zarzadcaLokacji_.anulujRezerwacjePlanety(planeta->pobierzIdentyfikator());
			return false;
		}
		return true;
	}

	int Gra::pobierzIloscGalaktyk() const{
		return zarzadcaLokacji_.pobierzIloscGalaktyk();
	}

	bool Gra::generujNowaGalaktyke(){
		return zarzadcaLokacji_.generujNowaGalaktyke();
	}

	Uzytkownik& Gra::pobierzUzytkownika() const throw (NieznalezionoObiektu) {
		if (!uzytkownik_)
			throw NieznalezionoObiektu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), STyp::Tekst("Uzytkownik"));
		return *uzytkownik_;
	}

	std::shared_ptr<Planeta> Gra::pobierzPlanete(const STyp::Identyfikator& identyfikator){
		return zarzadcaLokacji_.pobierzPlanete(identyfikator);
	}

	
	bool Gra::logowanie(const std::string& nazwa, const std::string& hash){
		uzytkownik_ = Aplikacja::pobierzInstancje().zarzadcaUzytkownikow_.logowanie(*this,nazwa,hash);
		return uzytkownik_.operator bool();
	}
	
	bool Gra::nowyGracz(const std::string& nazwa, const std::string& hash){
		return Aplikacja::pobierzInstancje().zarzadcaUzytkownikow_.nowyGracz(nazwa, hash);
	}

	bool Gra::usunGracza(const std::string& nazwa, const std::string& hash){
		return Aplikacja::pobierzInstancje().zarzadcaUzytkownikow_.usunGracza(*this, nazwa, hash);
	}
	
	bool Gra::wczytajDane(std::shared_ptr<SPar::ParserElement> root){
		try{			
			if (root){
				wczytajObiektyInfo<TechnologiaInfo>(root, listaTechnologiInfo_, WEZEL_XML_TECHNOLOGIA_INFO);
				wczytajObiektyInfo<BudynekInfo>(root, listaBudynkowInfo_, WEZEL_XML_BUDYNEK_INFO);
				wczytajObiektyInfo<SurowceInfo>(root, listaSurowcowInfo_, WEZEL_XML_SUROWCE_INFO);
				wczytajObiektyInfo<ObronaInfo>(root, listaObronaInfo_, WEZEL_XML_OBRONA_INFO);
				wczytajObiektyInfo<StatekInfo>(root, listaStatkowInfo_, WEZEL_XML_STATEK_INFO);
			}
		}
		catch (STyp::Wyjatek& wyjatek){
#ifndef LOG_OFF_ALL
			logger_.loguj(SLog::Log::Error, wyjatek.generujKomunikat());
#endif
			return false;
		}
		catch (std::exception& wyjatek){
#ifndef LOG_OFF_ALL
			logger_.loguj(SLog::Log::Error, wyjatek.what());
#endif
			return false;
		}
		return true;
	}
	
	const Gra::ListaObiektowInfoTyp& Gra::pobierzDostepneObiektyInfo(const Planeta& planeta, const STyp::Identyfikator& typObiektu, std::vector<STyp::Identyfikator>& listaId){
		listaId.reserve(listaObiektowInfo_.size());
		for (auto &element : listaObiektowInfo_){
			if ((typObiektu == 0 || element.second->typ_ == typObiektu)){
				PodstawoweParametry::AtrybutPodstawowy atrybut;
				auto obiekt = planeta.pobierzObiektJesliIstnieje<Obiekt>(element.first);
				if (obiekt != nullptr){
					atrybut = obiekt->pobierzAtrybut();
					if (obiekt->typAtrybutu() == PodstawoweParametry::POZIOM){
						++atrybut.poziom;
					}
				}else{
					atrybut = PodstawoweParametry::wartoscJednostkowaAtrybutu(element.second->pobierzTypAtrybutu());
				}

				if (element.second->czySpelniaWymagania(SpEx::PodstawoweParametry(atrybut, element.second->pobierzTypAtrybutu(), planeta.pobierzIdentyfikator()))){
					listaId.emplace_back(element.first);
				}
			}
		}
		return listaObiektowInfo_;
	}

	std::string Gra::napis() const{
		SLog::Logger logger(NAZWAKLASY(Gra));

		if (uzytkownik_){
			logger.dodajPole(NAZWAPOLA(uzytkownik_), uzytkownik_);
		}else{
			logger.dodajPole(NAZWAPOLA(uzytkownik_), NAZWAKLASY2(uzytkownik_),"nullptr");
		}

		logger.rozpocznijPodKlase(NAZWAPOLA(listaSurowcowInfo_), "SpEx::Gra::ListaSurowcowInfoTyp");
		for (auto& element : listaSurowcowInfo_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			logger.dodajPole("second", element.second);
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.rozpocznijPodKlase(NAZWAPOLA(listaStatkowInfo_), "SpEx::Gra::ListaStatkowInfoTyp");
		for (auto& element : listaStatkowInfo_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			logger.dodajPole("second", element.second);
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.rozpocznijPodKlase(NAZWAPOLA(listaObronaInfo_), "SpEx::Gra::ListaObronyInfoTyp");
		for (auto& element : listaObronaInfo_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			logger.dodajPole("second", element.second);
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.rozpocznijPodKlase(NAZWAPOLA(listaTechnologiInfo_), "SpEx::Gra::ListaTechnologiInfoTyp");
		for (auto& element : listaTechnologiInfo_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			logger.dodajPole("second", element.second);
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.rozpocznijPodKlase(NAZWAPOLA(listaBudynkowInfo_), "SpEx::Gra::ListaBudynkowInfoTyp");
		for (auto& element : listaBudynkowInfo_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			logger.dodajPole("second", element.second);
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		logger.rozpocznijPodKlase(NAZWAPOLA(listaObiektowInfo_), "SpEx::Gra::ListaObiektowInfoTyp");
		for (auto& element : listaObiektowInfo_){
			logger.rozpocznijPodKlase("Para");
			logger.dodajPole("first", element.first);
			logger.dodajPole("second", element.second);
			logger.zakonczPodKlase();
		}
		logger.zakonczPodKlase();

		return logger.napis();
	}
}
