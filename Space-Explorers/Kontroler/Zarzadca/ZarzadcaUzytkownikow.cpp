#include "ZarzadcaUzytkownikow.h"
#include "Parser\ParserDokumentXml.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\StackThrow.h"
#include "Logger\Logger.h"
#include <io.h>

#define ATRYBUT_FOLDER_PLIKU_UZYTKOWNIKA "folderPlikowUzytkownikow"
#define ATRYBUT_PLIK_AUTORYZACJI "plikAutoryzacji"

namespace SpEx{
	bool ZarzadcaUzytkownikow::inicjalizuj(const UstawieniaAplikacji& ustawienia, const std::function<std::string()>& stos){
		folderPlikowUzytkownika_ = ustawienia[ATRYBUT_FOLDER_PLIKU_UZYTKOWNIKA];
		plikAutoryzacji_ = ustawienia[ATRYBUT_PLIK_AUTORYZACJI];
		auto plikAutoryzacji = (folderPlikowUzytkownika_ + plikAutoryzacji_);
		if (_access(plikAutoryzacji.c_str(), 0) == -1){
			zapiszDane();
		}

		auto dokumentHash = std::make_shared<SPar::ParserDokumentXml>();
		if (dokumentHash->odczytaj(plikAutoryzacji.c_str())){
			return odczytaj(dokumentHash->pobierzElement(WEZEL_XML_ROOT));
		}
		return false;
	}
	
	bool ZarzadcaUzytkownikow::zapiszDane() const{
		auto dokumentHash = std::make_shared<SPar::ParserDokumentXml>();
		if (zapisz(dokumentHash->tworzElement(WEZEL_XML_ROOT)))
			return dokumentHash->zapisz((folderPlikowUzytkownika_ + plikAutoryzacji_).c_str());
		return false;
	}

	bool ZarzadcaUzytkownikow::zapisz(XmlBO::ElementWezla wezel) const{
		if (wezel != nullptr){
			std::lock_guard<std::mutex> lock(mutexAutoryzacja_);
			for (auto& para : autoryzacja_){
				auto uzytkownik = wezel->tworzElement(WEZEL_XML_UZYTKOWNIK);
				if (uzytkownik == nullptr){
					return false;
				}
				uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, para.first.c_str());
				uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, para.second.c_str());
			}
			return true;
		}
		return false;
	}
	
	bool ZarzadcaUzytkownikow::odczytaj(XmlBO::ElementWezla wezel){
		MapaAutoryzacji mapa;
		if (XmlBO::ForEach<SpEx::STACKTHROW>(wezel, WEZEL_XML_UZYTKOWNIK, XmlBO::OperacjaWezla([&mapa](XmlBO::ElementWezla element)->bool{

			auto nazwa = XmlBO::WczytajAtrybut<std::string>(element, ATRYBUT_XML_NAZWA, std::string());
			auto hash = XmlBO::WczytajAtrybut<std::string>(element, ATRYBUT_XML_HASH, std::string());

			if (hash.empty() || nazwa.empty())
				return false;

			auto iter = mapa.find(nazwa);
			if (iter != mapa.end())
				return false;

			mapa.emplace(std::make_pair(std::move(nazwa), std::move(hash)));
			return true;

		}))){
			std::lock_guard<std::mutex> lock(mutexAutoryzacja_);
			autoryzacja_.swap(mapa);
			return true;
		}
		return false;
	}
	
	std::string ZarzadcaUzytkownikow::pobierzHash(const std::string nazwaUzytkownika) const{
		std::lock_guard<std::mutex> lock(mutexAutoryzacja_);
		auto iter = autoryzacja_.find(nazwaUzytkownika);
		if (iter == autoryzacja_.end())
			return std::string();
		return iter->second;
	}

	std::shared_ptr<Uzytkownik> ZarzadcaUzytkownikow::logowanie(Gra& gra, const std::string& nazwa, const std::string& hash){
		std::string plik;
		auto dokument = plikUzytkownika(nazwa, hash, plik, false);
		if (!dokument)
			return false;
		auto nowyUzytkownik = std::make_shared<Uzytkownik>(gra);
		// TODO: Walidacja -> Walidator::pobierzInstancje().waliduj()
		if (nowyUzytkownik->odczytaj(dokument->pobierzElement(nullptr)))
			return nowyUzytkownik;
		else
			return nullptr;
	}

	bool ZarzadcaUzytkownikow::nowyGracz(const std::string& nazwa, const std::string& hash){
		std::string plik;
		if (plikUzytkownika(nazwa, hash, plik, false))
			return false;
		if (plikUzytkownika(nazwa, hash, plik) != nullptr){
			std::lock_guard<std::mutex> lock(mutexAutoryzacja_);
			autoryzacja_[nazwa] = hash;
			return true;
		}
		return false;
	}

	bool ZarzadcaUzytkownikow::zapiszGracza(std::shared_ptr<Uzytkownik> ptr){
		std::string plik;
		if (ptr == nullptr)
			return false;
		auto dokument = plikUzytkownika(ptr->pobierzNazweUzytkownika()(), ptr->pobierzSkrotKlucza()(), plik, true);
		if (!dokument || !ptr->zapisz(dokument->pobierzElement(nullptr)))
			return false;
		return dokument->zapisz(plik.c_str());
	}

	bool ZarzadcaUzytkownikow::usunGracza(Gra& gra, const std::string& nazwa, const std::string& hash){
		std::string plik;
		auto dokument = plikUzytkownika(nazwa, hash, plik, false);
		if (!dokument)
			return false;
		auto nowyUzytkownik = std::make_shared<Uzytkownik>(gra);
		// TODO: Walidacja -> Walidator::pobierzInstancje().waliduj()
		if (nowyUzytkownik->odczytaj(dokument->pobierzElement(nullptr)) ){
			//if (uzytkownik_ && nowyUzytkownik->pobierzNazweUzytkownika() == uzytkownik_->pobierzNazweUzytkownika())
			//	return false;
			nowyUzytkownik->odpinaniePlanet();
			std::lock_guard<std::mutex> lock(mutexAutoryzacja_);
			auto iter = autoryzacja_.find(nazwa);
			if (iter != autoryzacja_.end())
				autoryzacja_.erase(iter);
		} else
			return false;
		return !remove(plik.c_str());
	}

	std::shared_ptr<SPar::ParserDokument> ZarzadcaUzytkownikow::plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik) const{
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
		} else{
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

	std::string ZarzadcaUzytkownikow::napis() const{
		SLog::Logger logger(NAZWAKLASY(ZarzadcaUzytkownikow));
		logger.dodajPole(NAZWAPOLA(folderPlikowUzytkownika_), "std::string", folderPlikowUzytkownika_);
		{
			std::lock_guard<std::mutex> lock(mutexAutoryzacja_);
			logger.rozpocznijPodKlase(NAZWAPOLA(autoryzacja_));
			for (auto & para : autoryzacja_){
				logger.rozpocznijPodKlase("std::pair<std::string,std::string>");
				logger.dodajPole("first", "std::string", para.first);
				logger.dodajPole("second", "std::string", para.second);
				logger.zakonczPodKlase();
			}
			logger.zakonczPodKlase();
		}
		return logger.napis();
	}
}


