#include "Gra.h"
#include "Aplikacja.h"
#include "DefinicjeWezlowXML.h"
#include <iostream>
#include <fstream>
#include "Walidator.h"

namespace SpEx{

	Gra::Gra(Aplikacja& aplikacja, SZmi::ZmianaFabryka& fabryka)
		: aplikacja_(aplikacja), fabryka_(fabryka), uzytkownik_(nullptr)
	{
	}

	SZmi::ZmianaFabryka& Gra::pobierzFabrykeZmian() const{
		return fabryka_;
	}

	bool Gra::przeniesPlaneteDoUzytkownika(const STyp::Identyfikator& identyfikator){
		auto planeta = aplikacja_.pobierzZarzadce().pobierzPlanete(identyfikator);
		if (!planeta)
			return false;
		return uzytkownik_->dodajPlanete(planeta);
	}

	int Gra::pobierzIloscGalaktyk() const{
		return aplikacja_.pobierzZarzadce().pobierzIloscGalaktyk();
	}

	bool Gra::generujNowaGalaktyke(){
		return aplikacja_.pobierzZarzadce().generujNowaGalaktyke();
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
		return aplikacja_.pobierzZarzadce().pobierzPlanete(identyfikator);
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

	bool Gra::wczytajDane(std::shared_ptr<SPar::ParserElement> root){
		try{			
			if (root){
				if (!wczytajSurowce(root))
					return false;
				if (!wczytajStatki(root))
					return false;
				if (!wczytajObrone(root))
					return false;
				if (!wczytajTechnologie(root))
					return false;
				if (!wczytajBudynki(root))
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
		return aplikacja_.pobierzZarzadce().zapisz(wezel->tworzElement(WEZEL_XML_GRA));
	}

	bool Gra::odczytaj(XmlBO::ElementWezla wezel){
		if (wezel){
			auto element = XmlBO::ZnajdzWezel<NOTHROW>(wezel, WEZEL_XML_ZARZADCA);
			if (element)
				return aplikacja_.pobierzZarzadce().odczytaj(element);
			return true;
		}
		return false;
	}

	bool Gra::odczytaj(const std::string& nazwa, const std::string& hash){
		return logowanie(nazwa, hash);
	}

	bool Gra::logowanie(const std::string& nazwa, const std::string& hash){
		std::string plik;
		auto dokument = aplikacja_.pobierzZarzadce().plikUzytkownika(nazwa, hash, plik, false);
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
		if (aplikacja_.pobierzZarzadce().plikUzytkownika(nazwa, hash, plik, false))
			return false;
		return aplikacja_.pobierzZarzadce().plikUzytkownika(nazwa, hash, plik) != nullptr;
	}

	bool Gra::usunGracza(const std::string& nazwa, const std::string& hash){
		std::string plik;
		auto dokument = aplikacja_.pobierzZarzadce().plikUzytkownika(nazwa, hash, plik, false);
		if (!dokument)
			return false;
		return !remove(plik.c_str());
	}

	bool Gra::zapisz(const std::string& nazwa, const std::string& hash) const{
		std::string plik;
		auto dokument = aplikacja_.pobierzZarzadce().plikUzytkownika(nazwa, hash, plik, true);
		if (!dokument || !uzytkownik_->zapisz(dokument->pobierzElement(nullptr)))
			return false;
		return dokument->zapisz(plik.c_str());
	}
}
