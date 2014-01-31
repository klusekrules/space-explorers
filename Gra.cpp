#include "Gra.h"
#include "Aplikacja.h"
#include "DefinicjeWezlowXML.h"
#include <iostream>
#include <fstream>
#include "Walidator.h"
#include "Parser\ParserDokumentXml.h"

namespace SpEx{

	Gra::Gra(Aplikacja& aplikacja)
		: aplikacja_(aplikacja), fabryka_(SZmi::ZmianaFabryka::pobierzInstancje()), uzytkownik_(nullptr)
	{
	}

	Gra::Gra(const Gra& gra)
		: aplikacja_(gra.aplikacja_), fabryka_(SZmi::ZmianaFabryka::pobierzInstancje()), uzytkownik_(gra.uzytkownik_)
	{
	}

	Gra& Gra::operator=(const Gra& gra){
		return *this;
	}

	SZmi::ZmianaFabryka& Gra::pobierzFabrykeZmian() const{
		return fabryka_;
	}

	bool Gra::przeniesPlaneteDoUzytkownika(const STyp::Identyfikator& identyfikator){
		auto planeta = zarzadca_.pobierzPlanete(identyfikator);
		if (!planeta)
			return false;
		return uzytkownik_->dodajPlanete(planeta);
	}

	int Gra::pobierzIloscGalaktyk() const{
		return zarzadca_.pobierzIloscGalaktyk();
	}

	bool Gra::generujNowaGalaktyke(){
		return zarzadca_.generujNowaGalaktyke();
	}

	std::shared_ptr<Surowce> Gra::tworzSurowce(XmlBO::ElementWezla wezel)const{
		STyp::Identyfikator identyfikator;
		if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator))
			return nullptr;
		auto obiektOpisowy = listaSurowcowInfo_.find(identyfikator);
		if (obiektOpisowy == listaSurowcowInfo_.end())
			return nullptr;
		std::shared_ptr<Surowce> obiekt = std::shared_ptr<Surowce>(obiektOpisowy->second->tworzEgzemplarz(PodstawoweParametry(PodstawoweParametry::AtrybutPodstawowy(),PodstawoweParametry::ILOSC,STyp::Identyfikator())));
		if (!obiekt || !obiekt->odczytaj(wezel))
			return nullptr;
		return obiekt;
	}

	std::shared_ptr<Statek> Gra::tworzStatek(XmlBO::ElementWezla wezel)const{
		STyp::Identyfikator identyfikator;
		if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator))
			return nullptr;
		auto obiektOpisowy = listaStatkowInfo_.find(identyfikator);
		if (obiektOpisowy == listaStatkowInfo_.end())
			return nullptr;
		std::shared_ptr<Statek> obiekt = std::shared_ptr<Statek>(obiektOpisowy->second->tworzEgzemplarz(PodstawoweParametry(PodstawoweParametry::AtrybutPodstawowy(), PodstawoweParametry::ILOSC, STyp::Identyfikator())));
		if (!obiekt || !obiekt->odczytaj(wezel))
			return nullptr;
		return obiekt;
	}

	Uzytkownik& Gra::pobierzUzytkownika() const throw (NieznalezionoObiektu) {
		if (!uzytkownik_)
			throw NieznalezionoObiektu(EXCEPTION_PLACE, STyp::Tekst("Uzytkownik"));
		return *uzytkownik_;
	}

	std::shared_ptr<Planeta> Gra::pobierzPlanete(const STyp::Identyfikator& identyfikator){
		return zarzadca_.pobierzPlanete(identyfikator);
	}

	StatekInfo& Gra::pobierzStatek(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
		auto iterator = listaStatkowInfo_.find(identyfikator);
		if (iterator == listaStatkowInfo_.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		return *(iterator->second);
	}

	SurowceInfo& Gra::pobierzSurowce(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
		auto iterator = listaSurowcowInfo_.find(identyfikator);
		if (iterator == listaSurowcowInfo_.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		return *(iterator->second);
	}

	TechnologiaInfo& Gra::pobierzTechnologia(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
		auto iterator = listaTechnologiInfo_.find(identyfikator);
		if (iterator == listaTechnologiInfo_.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		return *(iterator->second);
	}

	BudynekInfo& Gra::pobierzBudynek(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
		auto iterator = listaBudynkowInfo_.find(identyfikator);
		if (iterator == listaBudynkowInfo_.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		return *(iterator->second);
	}

	ObiektInfo& Gra::pobierzObiekt(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
		auto iterator = listaObiektowInfo_.find(identyfikator);
		if (iterator == listaObiektowInfo_.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		return *(iterator->second);
	}

	ObronaInfo& Gra::pobierzObrone(const STyp::Identyfikator& identyfikator)const throw (NieznalezionoObiektu) {
		auto iterator = listaObronaInfo_.find(identyfikator);
		if (iterator == listaObronaInfo_.end())
			throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
		return *(iterator->second);
	}

	bool Gra::wczytajDane(const std::string& adresPliku){
		SPar::ParserDokumentXml dane;
		try{
			dane.odczytaj(adresPliku.c_str());
			auto root_data = dane.pobierzElement(WEZEL_XML_ROOT);
			if (root_data){
				if (!wczytajSurowce(root_data))
					return false;
				if (!wczytajStatki(root_data))
					return false;
				if (!wczytajObrone(root_data))
					return false;
				if (!wczytajTechnologie(root_data))
					return false;
				if (!wczytajBudynki(root_data))
					return false;
			}
		}
		catch (STyp::Wyjatek& wyjatek){
			aplikacja_.pobierzLogger().loguj(SLog::Log::Error, wyjatek.generujKomunikat());
			return false;
		}
		catch (std::exception& wyjatek){
			aplikacja_.pobierzLogger().loguj(SLog::Log::Error, wyjatek.what());
			return false;
		}
		return true;
	}

	bool Gra::wczytajTechnologie(XmlBO::ElementWezla wezel){
		try{
			XmlBO::ElementWezla element = wezel->pobierzElement(WEZEL_XML_TECHNOLOGIA_INFO);
			do{
				if (element){
					std::shared_ptr<TechnologiaInfo> obiekt = std::make_shared<TechnologiaInfo>(element);
					aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, *obiekt);
					if (listaObiektowInfo_.find(obiekt->pobierzIdentyfikator()) != listaObiektowInfo_.end())
						throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(""), STyp::Identyfikator(-1), STyp::Tekst("B³¹d wczytywania danych"), STyp::Tekst("Obiekt o podanym id istnieje"));
					listaTechnologiInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					listaObiektowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					element = element->pobierzNastepnyElement(WEZEL_XML_TECHNOLOGIA_INFO);
				}
			} while (element);
		}
		catch (STyp::Wyjatek& wyjatek){
			aplikacja_.pobierzLogger().loguj(SLog::Log::Warning, wyjatek.generujKomunikat());
			aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, wyjatek);
			return false;
		}
		return true;
	}

	bool Gra::wczytajBudynki(XmlBO::ElementWezla wezel){
		try{
			XmlBO::ElementWezla element = wezel->pobierzElement(WEZEL_XML_BUDYNEK_INFO);
			do{
				if (element){
					std::shared_ptr<BudynekInfo> obiekt(new BudynekInfo(element));
					aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, *obiekt);
					if (listaObiektowInfo_.find(obiekt->pobierzIdentyfikator()) != listaObiektowInfo_.end())
						throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(""), STyp::Identyfikator(-1), STyp::Tekst("B³¹d wczytywania danych"), STyp::Tekst("Obiekt o podanym id istnieje"));
					listaBudynkowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					listaObiektowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					element = element->pobierzNastepnyElement(WEZEL_XML_BUDYNEK_INFO);
				}
			} while (element);
		}
		catch (STyp::Wyjatek& wyjatek){
			aplikacja_.pobierzLogger().loguj(SLog::Log::Warning, wyjatek.generujKomunikat());
			aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, wyjatek);
			return false;
		}
		return true;
	}

	bool Gra::wczytajSurowce(XmlBO::ElementWezla wezel){
		try{
			XmlBO::ElementWezla element = wezel->pobierzElement(WEZEL_XML_SUROWCE_INFO);
			do{
				if (element){
					std::shared_ptr<SurowceInfo> obiekt(new SurowceInfo(element));
					aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, *obiekt);
					if (listaObiektowInfo_.find(obiekt->pobierzIdentyfikator()) != listaObiektowInfo_.end())
						throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(""), STyp::Identyfikator(-1), STyp::Tekst("B³¹d wczytywania danych"), STyp::Tekst("Obiekt o podanym id istnieje"));
					listaSurowcowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					listaObiektowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					element = element->pobierzNastepnyElement(WEZEL_XML_SUROWCE_INFO);
				}
			} while (element);
		}
		catch (STyp::Wyjatek& wyjatek){
			aplikacja_.pobierzLogger().loguj(SLog::Log::Warning, wyjatek.generujKomunikat());
			aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, wyjatek);
			return false;
		}
		return true;
	}

	bool Gra::wczytajObrone(XmlBO::ElementWezla wezel){
		try{
			XmlBO::ElementWezla element = wezel->pobierzElement(WEZEL_XML_OBRONA_INFO);
			do{
				if (element){
					std::shared_ptr<ObronaInfo> obiekt(new ObronaInfo(element));
					aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, *obiekt);
					if (listaObiektowInfo_.find(obiekt->pobierzIdentyfikator()) != listaObiektowInfo_.end())
						throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(""), STyp::Identyfikator(-1), STyp::Tekst("B³¹d wczytywania danych"), STyp::Tekst("Obiekt o podanym id istnieje"));
					listaObronaInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					listaObiektowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					element = element->pobierzNastepnyElement(WEZEL_XML_OBRONA_INFO);
				}
			} while (element);
		}
		catch (STyp::Wyjatek& wyjatek){
			aplikacja_.pobierzLogger().loguj(SLog::Log::Warning, wyjatek.generujKomunikat());
			aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, wyjatek);
			return false;
		}
		return true;
	}

	bool Gra::wczytajStatki(XmlBO::ElementWezla wezel){
		try{
			XmlBO::ElementWezla element = wezel->pobierzElement(WEZEL_XML_STATEK_INFO);
			do{
				if (element){
					std::shared_ptr<StatekInfo> obiekt(new StatekInfo(element));
					aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, *obiekt);
					if (listaObiektowInfo_.find(obiekt->pobierzIdentyfikator()) != listaObiektowInfo_.end())
						throw STyp::Wyjatek(EXCEPTION_PLACE, STyp::Tekst(""), STyp::Identyfikator(-1), STyp::Tekst("B³¹d wczytywania danych"), STyp::Tekst("Obiekt o podanym id istnieje"));
					listaStatkowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					listaObiektowInfo_[obiekt->pobierzIdentyfikator()] = obiekt;
					element = element->pobierzNastepnyElement(WEZEL_XML_STATEK_INFO);
				}
			} while (element);
		}
		catch (STyp::Wyjatek& wyjatek){
			aplikacja_.pobierzLogger().loguj(SLog::Log::Warning, wyjatek.generujKomunikat());
			aplikacja_.pobierzLogger().loguj(SLog::Log::Debug, wyjatek);
			return false;
		}
		return true;
	}

	bool Gra::zapisz(XmlBO::ElementWezla wezel) const{
		return zarzadca_.zapisz(wezel->tworzElement(WEZEL_XML_GRA));
	}

	bool Gra::odczytaj(XmlBO::ElementWezla wezel){
		if (wezel){
			auto element = XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_ZARZADCA);
			if (element)
				return zarzadca_.odczytaj(element);
			return true;
		}
		return false;
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
		return plikUzytkownika(nazwa, hash, plik) !=nullptr ;
	}

	bool Gra::usunGracza(const std::string& nazwa, const std::string& hash){
		std::string plik;
		auto dokument = plikUzytkownika(nazwa, hash, plik, false);
		if (!dokument)
			return false;
		return !remove(plik.c_str());
	}

	bool Gra::zapisz(const std::string& nazwa, const std::string& hash) const{
		std::string plik;
		auto dokument = plikUzytkownika(nazwa, hash, plik);
		if (!dokument || !uzytkownik_->zapisz(dokument->pobierzElement(nullptr)))
			return false;
		return dokument->zapisz(plik.c_str());
	}

	std::shared_ptr<SPar::ParserDokument> Gra::plikUzytkownika(const std::string& nazwa, const std::string& hash, std::string& nazwaPliku, bool tworzPlik) const{
		if (hash.empty() || nazwa.empty())
			return nullptr;
		std::string plik("save\\");
		plik.append(nazwa);
		plik.append("_.xml");
		std::shared_ptr<SPar::ParserDokument> dokument = std::make_shared<SPar::ParserDokumentXml>();
		if (dokument->odczytaj(plik.c_str()) == tinyxml2::XML_NO_ERROR){
			if (hash != XmlBO::WczytajAtrybut(dokument->pobierzElement(nullptr), "hash", std::string()))
				return nullptr;
			if (tworzPlik){
				dokument = std::make_shared<SPar::ParserDokumentXml>();
				dokument->odczytaj(plik.c_str());
				XmlBO::ElementWezla uzytkownik = dokument->tworzElement(WEZEL_XML_UZYTKOWNIK);
				uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, hash.c_str());
				uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa.c_str());
				dokument->zapisz(plik.c_str());
			}
		}
		else{
			if (!tworzPlik)
				return nullptr;
			XmlBO::ElementWezla uzytkownik = dokument->tworzElement(WEZEL_XML_UZYTKOWNIK);
			uzytkownik->tworzAtrybut(ATRYBUT_XML_HASH, hash.c_str());
			uzytkownik->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwa.c_str());
			dokument->zapisz(plik.c_str());
		}
		return dokument;
	}
}
