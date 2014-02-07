#define _USE_MATH_DEFINES
#include "Planeta.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "Walidator.h"

#define FMIN 0.0f
#define FMAX 1.0f

namespace SpEx{

	Planeta::Planeta(const STyp::Identyfikator& identyfikator, const STyp::Identyfikator& idUkladu)
		: identyfikator_(identyfikator),wlasciciel_(nullptr), idUkladu_(idUkladu)
	{
	}

	void Planeta::ustawWlasciciela(Uzytkownik* wlasciciel){
		wlasciciel_ = wlasciciel;
		idUzytkownika_ = wlasciciel_->pobierzNazweUzytkownika();
	}

	Uzytkownik* Planeta::pobierzWlasciciela(void) const{
		return wlasciciel_;
	}

	void Planeta::wyczyscZawartoscPlanety(){

		if (wlasciciel_ && !idUzytkownika_.isEmpty() && Aplikacja::pobierzInstancje().pobierzGre().pobierzUzytkownika().pobierzNazweUzytkownika() == idUzytkownika_){
			wlasciciel_->usunPlanete(pobierzIdentyfikator());
			wlasciciel_ = nullptr;
			idUzytkownika_ = STyp::Tekst();
		}
		licznikIdentyfikatorowFloty_.resetujWartosc();
		listaSurowcow_.clear();
		listaStatkow_.clear();
		listaObrona_.clear();
		listaTechnologii_.clear();
		listaBudynkow_.clear();
		listaObiektow_.clear();
		listaFlot_.clear();
	}

	STyp::Ilosc Planeta::pobierzIloscTypowObiektow()const{
		if (listaObiektow_.size() != listaBudynkow_.size() + listaStatkow_.size() + listaSurowcow_.size() + listaTechnologii_.size())
			throw NiepoprawnaIloscObiektow(EXCEPTION_PLACE, STyp::Ilosc(static_cast<long double>(listaObiektow_.size())));
		return STyp::Ilosc(static_cast<long double>(listaObiektow_.size()));
	}

	const Obiekt& Planeta::pobierzObiekt(const Indeks& identyfikator) const{
		auto iterator = listaObiektow_.find(identyfikator);
		if (iterator != listaObiektow_.end())
			return *(iterator->second);
		throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
	}
	
	STyp::Poziom Planeta::pobierzPoziomObiektu(const STyp::Identyfikator& identyfikator) const{
		auto iterator = listaObiektow_.end();
		for (auto element = listaObiektow_.begin(); element != listaObiektow_.end(); ++element){
			if (element->first == identyfikator && (iterator == listaObiektow_.end() || (iterator != listaObiektow_.end()))){
				iterator = element;
			}
		}
		if (iterator != listaObiektow_.end())
			return iterator->second->pobierzPoziom();
		return STyp::Poziom(0);
	}

	STyp::Ilosc Planeta::pobierzIloscObiektu(const Indeks& indeks) const{
		auto iterator = listaObiektow_.find(indeks);
		if (iterator != listaObiektow_.end())
			return iterator->second->pobierzIlosc();
		return STyp::Ilosc(0.0);
	}

	const Statek& Planeta::pobierzStatek(const Indeks& identyfikator) const{
		auto iterator = listaStatkow_.find(identyfikator);
		if (iterator != listaStatkow_.end())
			return *(iterator->second);
		throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
	}

	const Obrona& Planeta::pobierzObrone(const Indeks& identyfikator) const{
		auto iterator = listaObrona_.find(identyfikator);
		if (iterator != listaObrona_.end())
			return *(iterator->second);
		throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
	}

	const Technologia& Planeta::pobierzTechnologie(const Indeks& identyfikator) const{
		auto iterator = listaTechnologii_.find(identyfikator);
		if (iterator != listaTechnologii_.end())
			return *(iterator->second);
		throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
	}

	const Budynek& Planeta::pobierzBudynek(const Indeks& identyfikator) const{
		auto iterator = listaBudynkow_.find(identyfikator);
		if (iterator != listaBudynkow_.end())
			return *(iterator->second);
		throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Budynek > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		listaBudynkow_.insert(make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Obrona > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		listaObrona_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Statek > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		listaStatkow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Technologia > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		listaTechnologii_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Surowce > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		listaSurowcow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::wybuduj(const Indeks& identyfikator, const PodstawoweParametry& ilosc){
		auto iterator = listaObiektow_.find(identyfikator);
		if (iterator != listaObiektow_.end()){
			iterator->second->wybuduj(ilosc);
			return true;
		}
		else{
			return false; Aplikacja::pobierzInstancje().pobierzGre().pobierzObiekt(identyfikator).tworz(*this, ilosc.pobierzAtrybut());
		}
	}

	/*bool Planeta::wybuduj(const BudynekInfo& obiektInfo, const PodstawoweParametry& parametry ){
		return dodajObiekt(std::shared_ptr<Budynek>(obiektInfo.tworzEgzemplarz(parametry)));
	}

	bool Planeta::wybuduj(const TechnologiaInfo& obiektInfo, const PodstawoweParametry& parametry){
		return dodajObiekt(std::shared_ptr<Technologia>(obiektInfo.tworzEgzemplarz(parametry)));
	}

	bool Planeta::wybuduj(const StatekInfo& obiektInfo, const PodstawoweParametry& parametry){
		return dodajObiekt(std::shared_ptr<Statek>(obiektInfo.tworzEgzemplarz(parametry)));
	}

	bool Planeta::wybuduj(const SurowceInfo& obiektInfo, const PodstawoweParametry& parametry){
		return dodajObiekt(std::shared_ptr<Surowce>(obiektInfo.tworzEgzemplarz(parametry)));
	}

	bool Planeta::wybuduj(const ObronaInfo& obiektInfo, const PodstawoweParametry& parametry){
		return dodajObiekt(std::shared_ptr<Obrona>(obiektInfo.tworzEgzemplarz(parametry)));
	}*/

	/*void Planeta::wybuduj(std::shared_ptr< Obiekt > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			iterator->second->wybuduj(*obiekt);
		}
		else{
			//TODO: Aplikacja::pobierzInstancje().pobierzGre().wybudujNaPlanecie(*this, , obiekt->pobierzIlosc(), obiekt->pobierzPoziom());
		}
	}

	void Planeta::wybuduj(std::shared_ptr< Statek > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			iterator->second->wybuduj(*obiekt);
		}
		else{
			dodajObiekt(obiekt);
		}
	}*/

	STyp::Identyfikator Planeta::dodajFlote(){
		std::shared_ptr< Flota > flota = std::shared_ptr< Flota >(new Flota(STyp::Identyfikator(static_cast<STyp::Identyfikator::nazwa_typu>(licznikIdentyfikatorowFloty_()())), STyp::Identyfikator(), STyp::Identyfikator(), Flota::CelPodrozy::Transport));
		listaFlot_.insert(std::make_pair(flota->pobierzIdentyfikator(), flota));
		return flota->pobierzIdentyfikator();
	}

	bool Planeta::przeniesDoFloty(const STyp::Identyfikator& identyfikatorFloty, const Indeks& obiekt, const STyp::Ilosc& ilosc){
		auto statek = listaStatkow_.find(obiekt);
		if (statek != listaStatkow_.end()){
			auto flota = listaFlot_.find(identyfikatorFloty);
			if (flota != listaFlot_.end()){
				if (ilosc <= statek->second->pobierzIlosc()){
					if (ilosc < statek->second->pobierzIlosc()){
						auto podzial = std::shared_ptr<Statek>(statek->second->podziel(ilosc));
						if (flota->second->dodajStatek(podzial)){
							return true;
						}
						else{
							statek->second->polacz(*podzial);
							return false;
						}
					}
					else{
						if (flota->second->dodajStatek(statek->second)){
							listaStatkow_.erase(obiekt);
							listaObiektow_.erase(obiekt);
							return true;
						}
						else{
							return false;
						}
					}
				}
			}
		}
		return false;
	}

	bool Planeta::zaladujSurowceNaFlote(const STyp::Identyfikator& identyfikatorFloty, const Indeks& identyfikator, const STyp::Ilosc& ilosc){
		auto iterator = listaSurowcow_.find(identyfikator);
		if (iterator == listaSurowcow_.end())
			return false;

		if (ilosc <= STyp::Ilosc(0.0) || iterator->second->pobierzIlosc() < ilosc)
			return false;

		auto flota = listaFlot_.find(identyfikatorFloty);
		if (flota == listaFlot_.end())
			return false;
		std::shared_ptr<Surowce> ladunek = std::shared_ptr<Surowce>(iterator->second->podziel(ilosc));
		if (!flota->second->dodajLadunek(ladunek)){
			iterator->second->polacz(*ladunek);
			return false;
		}
		return true;
	}

	bool Planeta::zaladujStatekNaFlote(const STyp::Identyfikator& identyfikatorFloty, const Indeks& identyfikator, const STyp::Ilosc& ilosc){
		auto iterator = listaStatkow_.find(identyfikator);
		if (iterator == listaStatkow_.end())
			return false;

		if (ilosc <= STyp::Ilosc(0.0) || iterator->second->pobierzIlosc() < ilosc)
			return false;

		auto flota = listaFlot_.find(identyfikatorFloty);
		if (flota == listaFlot_.end())
			return false;
		std::shared_ptr<Statek> ladunek = std::shared_ptr<Statek>(iterator->second->podziel(ilosc));
		if (!flota->second->dodajLadunek(ladunek)){
			iterator->second->polacz(*ladunek);
			return false;
		}
		return true;
	}

	bool Planeta::czyMaWlasciciela()const{
		return wlasciciel_ != nullptr;
	}
	/*
	void Planeta::rozladujStatek(std::shared_ptr< Statek > statek){
		if (statek){
			for (auto element : statek->oproznijLadownie()){
				wybuduj(element.second);
			}
			for (auto element : statek->oproznijHangar()){
				wybuduj(element.second);
			}
		}
	}*/

	std::shared_ptr< Flota > Planeta::pobierzFlote(const STyp::Identyfikator& identyfikator) const{
		auto iterator = listaFlot_.find(identyfikator);
		if (iterator != listaFlot_.end())
			return iterator->second;
		return nullptr;
	}

	bool Planeta::usunFlote(const STyp::Identyfikator& identyfikator){
		return listaFlot_.erase(identyfikator) != 0;
	}

	bool Planeta::zapisz(XmlBO::ElementWezla wezel) const{
		auto planeta = wezel->tworzElement(WEZEL_XML_PLANETA);
		planeta->tworzAtrybut(ATRYBUT_XML_ODLEGLOSC_OD_SLONCA, odlegloscOdSlonca_.napis().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_SREDNICA, srednicaPlanety_.napis().c_str());
		/*planeta->SetAttribute(ATRYBUT_XML_PREDKOSC_KATOWA_PLANETY, predkoscKatowaPlanety_.napis());
		planeta->SetAttribute(ATRYBUT_XML_NASLONECZNIENIE_PLANETY, naslonecznieniePlanety_.napis());
		planeta->SetAttribute(ATRYBUT_XML_WIETRZNOSC_PLANETY, wietrznoscPlanety_.napis());*/
		planeta->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR_RODZICA, idUkladu_.napis().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_NAZWAGRACZA, idUzytkownika_().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_TEMPERATURA_PLANETY, temperaturaPlanety_.napis().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_CALKOWITA_POWIERZNIA_PLANETY, calkowitaPowierzchniaPlanety_.napis().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA_ZAJETA_PRZEZ_WODE, powierzchniaZajetaPrzezWode_.napis().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA_LADOW, powierzchniaLadow_.napis().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA_UZYTKOWA_LADOW, powierzchniaUzytkowaLadow_.napis().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwaPlanety_().c_str());
		licznikIdentyfikatorowFloty_.zapisz(planeta);
		/*for(auto element :  dostepneZasobyPlanety_){
			TiXmlElement* zasob = new TiXmlElement(WEZEL_XML_ZASOB);
			zasob->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR, element.first.pobierzIdentyfikator().napis());
			zasob->SetAttribute(ATRYBUT_XML_POZIOM, element.first.pobierzPoziom().napis());
			zasob->SetAttribute(ATRYBUT_XML_ILOSC, element.second.napis());
			planeta->LinkEndChild(zasob);
			}*/
		auto obiekty = wezel->tworzElement(WEZEL_XML_OBIEKTY);
		for (auto element : listaObiektow_)
		if (!element.second->zapisz(obiekty))
			return false;
		auto floty = wezel->tworzElement(WEZEL_XML_FLOTY);
		for (auto element : listaFlot_)
		if (!element.second->zapisz(floty))
			return false;
		return true;//TODO: zapis identyfikatora planety
	}

	bool Planeta::odczytaj(XmlBO::ElementWezla wezel){
		if (wezel){
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_ODLEGLOSC_OD_SLONCA, odlegloscOdSlonca_))
				return false;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_SREDNICA, srednicaPlanety_))
				return false;
			/*if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_PREDKOSC_KATOWA_PLANETY,predkoscKatowaPlanety_))
				return false;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NASLONECZNIENIE_PLANETY,naslonecznieniePlanety_))
				return false;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_WIETRZNOSC_PLANETY,wietrznoscPlanety_))
				return false;*/
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_RODZICA, idUkladu_))
				return false;

			XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_NAZWAGRACZA, idUzytkownika_);

			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_TEMPERATURA_PLANETY, temperaturaPlanety_))
				return false;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_CALKOWITA_POWIERZNIA_PLANETY, calkowitaPowierzchniaPlanety_))
				return false;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_ZAJETA_PRZEZ_WODE, powierzchniaZajetaPrzezWode_))
				return false;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_LADOW, powierzchniaLadow_))
				return false;
			if (!XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_UZYTKOWA_LADOW, powierzchniaUzytkowaLadow_))
				return false;
			XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_NAZWA, nazwaPlanety_);
			XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
			Walidator::pobierzInstancje().dodajNowyIdentyfikatorPlanety(identyfikator_);
			//TODO: Uzycie foreach
			for (auto zasob = wezel->pobierzElement(WEZEL_XML_ZASOB); zasob; zasob = zasob->pobierzNastepnyElement(WEZEL_XML_ZASOB)){
				STyp::Identyfikator identyfikator;
				STyp::Poziom poziom;
				STyp::Ilosc ilosc;
				if (!XmlBO::WczytajAtrybut<NOTHROW>(zasob, ATRYBUT_XML_IDENTYFIKATOR, identyfikator))
					return false;
				if (!XmlBO::WczytajAtrybut<NOTHROW>(zasob, ATRYBUT_XML_POZIOM, poziom))
					return false;
				if (!XmlBO::WczytajAtrybut<NOTHROW>(zasob, ATRYBUT_XML_ILOSC, ilosc))
					return false;
				/*auto iter = dostepneZasobyPlanety_.find(Indeks(identyfikator,poziom));
				if( iter != dostepneZasobyPlanety_.end())
				return false;
				dostepneZasobyPlanety_.insert(make_pair(Indeks(identyfikator,poziom),ilosc));*/
			}

			auto obiekt = wezel->pobierzElement(WEZEL_XML_OBIEKTY);
			if (obiekt)
			for (auto element = obiekt->pobierzElement(nullptr); element; element = element->pobierzNastepnyElement(nullptr)){
				STyp::Identyfikator identyfikator;
				STyp::Poziom poziom;
				if (!XmlBO::WczytajAtrybut<NOTHROW>(element, ATRYBUT_XML_IDENTYFIKATOR, identyfikator))
					return false;
				if (!XmlBO::WczytajAtrybut<NOTHROW>(element, ATRYBUT_XML_POZIOM, poziom))
					return false;
				//TODO: Stworzenie zamiennika budowania obiektu
				/*if (!wybuduj(Indeks(identyfikator, poziom), element))
					return false;*/
				auto iter = listaObiektow_.find(identyfikator);
				if (iter == listaObiektow_.end())
					return false;
				if (iter->second->pobierzIdentyfikatorPlanety() != identyfikator_)
					return false;
			}
			auto flota = wezel->pobierzElement(WEZEL_XML_FLOTY);
			if (flota)
			for (auto element = flota->pobierzElement(nullptr); element; element = element->pobierzNastepnyElement(nullptr)){
				STyp::Identyfikator identyfikator;
				if (!XmlBO::WczytajAtrybut<NOTHROW>(element, ATRYBUT_XML_IDENTYFIKATOR, identyfikator))
					return false;
				std::shared_ptr<Flota> wskaznik = std::shared_ptr<Flota>(new Flota(identyfikator, STyp::Identyfikator(), STyp::Identyfikator(), Flota::CelPodrozy::Transport));
				auto iterator = listaFlot_.find(identyfikator);
				if (iterator != listaFlot_.end() || !wskaznik->odczytaj(element))
					return false;
				if (wskaznik->pobierzPlanetePoczatkowa() != identyfikator_)
					return false;
				Walidator::pobierzInstancje().dodajUzytyIdentyfikatorPlanety(wskaznik->pobierzPlanetePoczatkowa());
				Walidator::pobierzInstancje().dodajUzytyIdentyfikatorPlanety(wskaznik->pobierzPlaneteDocelowa());
				listaFlot_.insert(std::make_pair(wskaznik->pobierzIdentyfikator(), wskaznik));
			}
			return true;
		}
		return false;
	}

	STyp::Tekst Planeta::pobierzNazwePlanety() const{
		return nazwaPlanety_;
	}

	void Planeta::ustawNazwePlanety(const STyp::Tekst& nazwa){
		nazwaPlanety_ = nazwa;
	}

	const STyp::Identyfikator& Planeta::pobierzIdUkladu() const{
		return idUkladu_;
	}

	void Planeta::ustawTemperature(const STyp::Temperatura& temperatura){
		temperaturaPlanety_ = temperatura;
	}

	void Planeta::ustawSrednice(const STyp::Dystans& srednica){
		srednicaPlanety_ = srednica;
	}

	void Planeta::ustawOdlegloscOdSrodkaUkladu(const STyp::Dystans& odleglosc){
		odlegloscOdSlonca_ = odleglosc;
	}

	bool Planeta::wyliczPowierzchnie(const STyp::Fluktuacja& procentWody, const STyp::Fluktuacja& procentUzytkowa){
		if (procentWody > STyp::Fluktuacja(FMAX) || procentWody < STyp::Fluktuacja(FMIN) || //TODO: Zmiennik dla fluktuacja min max
			procentUzytkowa > STyp::Fluktuacja(FMAX) || procentUzytkowa < STyp::Fluktuacja(FMIN))
			return false;
		STyp::SPG::Powierzchnia calkowita = M_PI * srednicaPlanety_() * srednicaPlanety_();
		calkowitaPowierzchniaPlanety_(calkowita);
		powierzchniaZajetaPrzezWode_(calkowita * procentWody());
		powierzchniaLadow_(calkowita * (FMAX - procentWody()));
		powierzchniaUzytkowaLadow_(powierzchniaLadow_() * procentUzytkowa());
		return true;
	}

	const STyp::Identyfikator& Planeta::pobierzIdentyfikator()const{
		return identyfikator_;
	}

	std::string Planeta::napis() const{
		SLog::Logger str(NAZWAKLASY(Planeta));
		str.dodajPole(NAZWAKLASY(Licznik), licznikIdentyfikatorowFloty_);
		str.dodajPole("odlegloscOdSlonca", odlegloscOdSlonca_);
		//str.dodajPole("predkoscKatowaPlanety",predkoscKatowaPlanety_);
		//str.dodajPole("naslonecznieniePlanety",naslonecznieniePlanety_);
		str.dodajPole("idUkladu", idUkladu_);
		str.dodajPole("temperaturaPlanety", temperaturaPlanety_);
		str.dodajPole("calkowitaPowierzchniaPlanety", calkowitaPowierzchniaPlanety_);
		str.dodajPole("powierzchniaZajetaPrzezWode", powierzchniaZajetaPrzezWode_);
		str.dodajPole("powierzchniaLadow", powierzchniaLadow_);
		str.dodajPole("powierzchniaUzytkowaLadow", powierzchniaUzytkowaLadow_);
		str.dodajPole("nazwaPlanety", nazwaPlanety_);
		//for( auto element : dostepneZasobyPlanety_ )
		//	str.dodajPole("Zasob", element.second);
		for (auto element : listaObiektow_)
			str.dodajPole("Obiekt", *(element.second));
		for (auto element : listaFlot_)
			str.dodajPole("Flota", *(element.second));
		return str.napis();
	}
}
