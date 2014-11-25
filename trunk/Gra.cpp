#include "Gra.h"
#include "DefinicjeWezlowXML.h"
#include <iostream>
#include <fstream>
#include "Walidator.h"
#include "Parser\ParserDokumentXml.h"

namespace SpEx{

	Gra::Gra(SLog::Log& logger, ZarzadcaLokacji& zarzadcaLokacji, UstawieniaAplikacji& ustawieniaAplikacji)
		: logger_(logger), zarzadcaLokacji_(zarzadcaLokacji), folderPlikowUzytkownika_(ustawieniaAplikacji.pobierzFolderPlikuUzytkownika()), uzytkownik_(nullptr)
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
		auto ptr = zarzadcaLokacji_.pobierzPlanete(identyfikator);
		if (!ptr)
			throw NieznalezionoObiektu(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), std::to_string(identyfikator()));
		return ptr;
	}
	
	bool Gra::wczytajDane(std::shared_ptr<SPar::ParserElement> root){
		try{			
			if (root){
				wczytajObiekty<TechnologiaInfo>(root, listaTechnologiInfo_, WEZEL_XML_TECHNOLOGIA_INFO);
				wczytajObiekty<BudynekInfo>(root, listaBudynkowInfo_, WEZEL_XML_BUDYNEK_INFO);
				wczytajObiekty<SurowceInfo>(root, listaSurowcowInfo_, WEZEL_XML_SUROWCE_INFO);
				wczytajObiekty<ObronaInfo>(root, listaObronaInfo_, WEZEL_XML_OBRONA_INFO);
				wczytajObiekty<StatekInfo>(root, listaStatkowInfo_, WEZEL_XML_STATEK_INFO);
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
	
	bool Gra::odczytaj(const std::string& nazwa, const std::string& hash){
		return logowanie(nazwa, hash);
	}

	bool Gra::logowanie(const std::string& nazwa, const std::string& hash){
		std::string plik;
		auto dokument = plikUzytkownika(nazwa, hash, plik, false);
		if (!dokument)
			return false;
		auto nowyUzytkownik = std::make_shared<Uzytkownik>(*this);
		if (nowyUzytkownik->odczytaj(dokument->pobierzElement(nullptr)) && Walidator::pobierzInstancje().waliduj())
			uzytkownik_ = nowyUzytkownik;
		else
			return false;
		return true;
	}

	bool Gra::nowyGracz(const std::string& nazwa, const std::string& hash){
		std::string plik;
		if (plikUzytkownika(nazwa, hash, plik, false))
			return false;
		return plikUzytkownika(nazwa, hash, plik) != nullptr;
	}

	bool Gra::usunGracza(const std::string& nazwa, const std::string& hash){
		std::string plik;
		auto dokument = plikUzytkownika(nazwa, hash, plik, false);
		if (!dokument)
			return false;
		auto nowyUzytkownik = std::make_shared<Uzytkownik>(*this);
		if (nowyUzytkownik->odczytaj(dokument->pobierzElement(nullptr)) && Walidator::pobierzInstancje().waliduj()){
			if (uzytkownik_ && nowyUzytkownik->pobierzNazweUzytkownika() == uzytkownik_->pobierzNazweUzytkownika())
				return false;
			nowyUzytkownik->odpinaniePlanet();
		}
		else
			return false;
		return !remove(plik.c_str());
	}

	bool Gra::zapisz(const std::string& nazwa, const std::string& hash) const{
		std::string plik;
		auto dokument = plikUzytkownika(nazwa, hash, plik, true);
		if (!dokument || !uzytkownik_ || !uzytkownik_->zapisz(dokument->pobierzElement(nullptr)))
			return false;
		return dokument->zapisz(plik.c_str());
	}

	std::shared_ptr<SPar::ParserDokument> Gra::plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik) const{
		if (hash.empty() || nazwa.empty())
			return nullptr;
		std::string plik = folderPlikowUzytkownika_.c_str();
		plik.append(nazwa);
		plik.append("_.xml");
		auto dokument = std::make_shared<SPar::ParserDokumentXml>();
		if (dokument->odczytaj(plik.c_str())){
			if (hash != XmlBO::WczytajAtrybut(dokument->pobierzElement(nullptr), "hash", std::string()))
				return nullptr;
			if (tworzPlik){
				dokument = std::make_shared<SPar::ParserDokumentXml>();
				XmlBO::ElementWezla uzytkownik = dokument->tworzElement(WEZEL_XML_UZYTKOWNIK);
				uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, hash.c_str());
				uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa.c_str());
				uzytkownik->tworzAtrybut(ATRYBUT_XML_PLANETA_AKTYWNA, std::to_string(STyp::Identyfikator(0)()).c_str());
				dokument->zapisz(plik.c_str());
			}
		}
		else{
			if (!tworzPlik)
				return nullptr;
			XmlBO::ElementWezla uzytkownik = dokument->tworzElement(WEZEL_XML_UZYTKOWNIK);
			uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, hash.c_str());
			uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa.c_str());
			uzytkownik->tworzAtrybut(ATRYBUT_XML_PLANETA_AKTYWNA, std::to_string(STyp::Identyfikator(0)()).c_str());
			dokument->zapisz(plik.c_str());
		}
		nazwaPliku = plik;
		return dokument;
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
}
