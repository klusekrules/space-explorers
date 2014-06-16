#define _USE_MATH_DEFINES
#include "Planeta.h"
#include "Aplikacja.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "Walidator.h"
#include <functional>

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

	const Planeta::ListaSurowcow& Planeta::pobierzSurowce()const{
		return listaSurowcow_;
	}

	bool Planeta::odepnijPlanete(){
		if (wlasciciel_){
			return wlasciciel_->odpinaniePlanet(identyfikator_);
		}
		return true;
	}

	void Planeta::wyczyscZawartoscPlanety(){
		//TODO: Sprawdzanie praw dostêpu.
		if (wlasciciel_){
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
		return STyp::Ilosc(static_cast<long double>(listaObiektow_.size()));
	}

	const Obiekt& Planeta::pobierzObiekt(const Indeks& identyfikator) const{
		auto iterator = listaObiektow_.find(identyfikator);
		if (iterator != listaObiektow_.end())
			return *(iterator->second);
		throw NieznalezionoObiektu(EXCEPTION_PLACE, identyfikator.napis());
	}

	std::shared_ptr< Obiekt > Planeta::pobierzObiektJesliIstnieje(const Indeks& identyfikator) const{
		auto iterator = listaObiektow_.find(identyfikator);
		if (iterator != listaObiektow_.end())
			return iterator->second;
		return nullptr;
	}
	
	STyp::Poziom Planeta::pobierzPoziomObiektu(const Indeks& identyfikator) const{
		auto iterator = listaObiektow_.find(identyfikator);
		if (iterator != listaObiektow_.end() && iterator->second->typAtrybutu() == PodstawoweParametry::POZIOM)
			return iterator->second->pobierzPoziom();
		return STyp::Poziom(0);
	}

	STyp::Ilosc Planeta::pobierzIloscObiektu(const Indeks& indeks) const{
		auto iterator = listaObiektow_.find(indeks);
		if (iterator != listaObiektow_.end() && iterator->second->typAtrybutu() == PodstawoweParametry::ILOSC)
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
		obiekt->ustawIdentyfikatorPlanety(identyfikator_);
		listaBudynkow_.insert(make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Obrona > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		obiekt->ustawIdentyfikatorPlanety(identyfikator_);
		listaObrona_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Statek > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		obiekt->ustawIdentyfikatorPlanety(identyfikator_);
		listaStatkow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Technologia > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		obiekt->ustawIdentyfikatorPlanety(identyfikator_);
		listaTechnologii_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		listaObiektow_.insert(std::make_pair(obiekt->pobierzIdentyfikator(), obiekt));
		return true;
	}

	bool Planeta::dodajObiekt(std::shared_ptr< Surowce > obiekt){
		auto iterator = listaObiektow_.find(obiekt->pobierzIdentyfikator());
		if (iterator != listaObiektow_.end()){
			return iterator->second->polacz(*obiekt);
		}
		obiekt->ustawIdentyfikatorPlanety(identyfikator_);
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
			return Aplikacja::pobierzInstancje().pobierzGre().pobierzObiekt(identyfikator).tworz(*this, ilosc.pobierzAtrybut());
		}
	}

	bool Planeta::wybuduj(const Indeks& identyfikator, const XmlBO::ElementWezla element){
		auto iterator = listaObiektow_.find(identyfikator);
		if (iterator != listaObiektow_.end()){
			return false;
		}else{
			return Aplikacja::pobierzInstancje().pobierzGre().pobierzObiekt(identyfikator).tworz(*this, element);
		}
	}

	Planeta::Indeks Planeta::dodajFlote(){
		auto flota = std::make_shared< Flota >(STyp::Identyfikator(static_cast<STyp::Identyfikator::nazwa_typu>(licznikIdentyfikatorowFloty_()())), STyp::Identyfikator(), STyp::Identyfikator(), Flota::CelPodrozy::Transport);
		listaFlot_.insert(std::make_pair(flota->pobierzIdentyfikator(), flota));
		return flota->pobierzIdentyfikator();
	}

	bool Planeta::przeniesDoFloty(const Indeks& identyfikatorFloty, const Indeks& obiekt, const STyp::Ilosc& ilosc){
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

	bool Planeta::zaladujSurowceNaFlote(const Indeks& identyfikatorFloty, const Indeks& identyfikator, const STyp::Ilosc& ilosc){
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

	bool Planeta::zaladujStatekNaFlote(const Indeks& identyfikatorFloty, const Indeks& identyfikator, const STyp::Ilosc& ilosc){
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
	
	void Planeta::rozladujStatek(std::shared_ptr< Statek > statek){
		if (statek){
			for (auto element : statek->oproznijLadownie()){
				dodajObiekt(element.second);
			}
			for (auto element : statek->oproznijHangar()){
				dodajObiekt(element.second);
			}
		}
	}

	std::shared_ptr< Flota > Planeta::pobierzFlote(const Indeks& identyfikator) const{
		auto iterator = listaFlot_.find(identyfikator);
		if (iterator != listaFlot_.end())
			return iterator->second;
		return nullptr;
	}

	bool Planeta::usunFlote(const Indeks& identyfikator){
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
		planeta->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, identyfikator_.napis().c_str());
		licznikIdentyfikatorowFloty_.zapisz(planeta);
		/* Nie u¿ywana funkcjonalnoœæ
		for (auto element : dostepneZasobyPlanety_){
			auto zasob = planeta->tworzElement(WEZEL_XML_ZASOB);
			zasob->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, element.first.napis().c_str());
			zasob->tworzAtrybut(ATRYBUT_XML_ILOSC, element.second.napis().c_str());
		}*/
		auto obiekty = planeta->tworzElement(WEZEL_XML_OBIEKTY);
		for (auto element : listaObiektow_){
			if (!element.second->zapisz(obiekty))
				return false;
		}
		auto floty = planeta->tworzElement(WEZEL_XML_FLOTY);
		for (auto element : listaFlot_){
			if (!element.second->zapisz(floty))
				return false;
		}
		return true;
	}

	bool Planeta::odczytaj(XmlBO::ElementWezla wezel){
		if (wezel){

			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, identyfikator_);
			Walidator::pobierzInstancje().dodajNowyIdentyfikatorPlanety(identyfikator_);

			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_NAZWA, nazwaPlanety_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ODLEGLOSC_OD_SLONCA, odlegloscOdSlonca_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_SREDNICA, srednicaPlanety_);
			/*if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_PREDKOSC_KATOWA_PLANETY,predkoscKatowaPlanety_))
				return false;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NASLONECZNIENIE_PLANETY,naslonecznieniePlanety_))
				return false;
				if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_WIETRZNOSC_PLANETY,wietrznoscPlanety_))
				return false;*/
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_RODZICA, idUkladu_);
			XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_NAZWAGRACZA, idUzytkownika_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_TEMPERATURA_PLANETY, temperaturaPlanety_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_CALKOWITA_POWIERZNIA_PLANETY, calkowitaPowierzchniaPlanety_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_ZAJETA_PRZEZ_WODE, powierzchniaZajetaPrzezWode_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_LADOW, powierzchniaLadow_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_UZYTKOWA_LADOW, powierzchniaUzytkowaLadow_);

			/* Nie u¿ywana funkcjonalnoœæ
			if (!XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_ZASOB, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla zasob)->bool{
				STyp::Identyfikator identyfikator;
				STyp::Ilosc ilosc;
				XmlBO::WczytajAtrybut<STACKTHROW>(zasob, ATRYBUT_XML_IDENTYFIKATOR, identyfikator);
				XmlBO::WczytajAtrybut<STACKTHROW>(zasob, ATRYBUT_XML_ILOSC, ilosc);
				auto iter = dostepneZasobyPlanety_.find(identyfikator);
				if (iter != dostepneZasobyPlanety_.end())
					return false;
				dostepneZasobyPlanety_.insert(std::make_pair(identyfikator, ilosc));
				return true;
			}))){
				return false;
			}*/

			auto obiekt = wezel->pobierzElement(WEZEL_XML_OBIEKTY);
			if (obiekt){
				if (!XmlBO::ForEach<STACKTHROW>(obiekt, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
					Indeks identyfikator;
					XmlBO::WczytajAtrybut<STACKTHROW>(element, ATRYBUT_XML_IDENTYFIKATOR, identyfikator);
					if (!wybuduj(identyfikator, element))
						return false;
					auto iter = listaObiektow_.find(identyfikator);
					if (iter == listaObiektow_.end())
						return false;
					if (iter->second->pobierzIdentyfikatorPlanety() != identyfikator_)
						return false;
					return true;
				}))){
					return false;
				}
			}

			// Sprawdzanie spójnoœci obiektów na planecie.
			if (listaObiektow_.size() != listaBudynkow_.size() + listaStatkow_.size() + listaSurowcow_.size() + listaTechnologii_.size() + listaObrona_.size()){
				throw STyp::Wyjatek(EXCEPTION_PLACE, Aplikacja::pobierzInstancje().pobierzSladStosu(), STyp::Identyfikator(145), STyp::Tekst("Niespójnoœæ danych!"),
					STyp::Tekst("Wykryto niespójnoœæ danych obiektów znajduj¹cych siê na planecie o id = " + identyfikator_.napis()
					+ ". Iloœæ typów wszystkich obiektów = " + std::to_string(listaObiektow_.size())
					+ ". Iloœæ typów budynków = " + std::to_string(listaBudynkow_.size())
					+ ". Iloœæ typów statków = " + std::to_string(listaStatkow_.size())
					+ ". Iloœæ typów surowców = " + std::to_string(listaSurowcow_.size())
					+ ". Iloœæ typów technologii = " + std::to_string(listaTechnologii_.size())
					+ ". Iloœæ typów obrony = " + std::to_string(listaObrona_.size()) + "."));
			}

			auto flota = wezel->pobierzElement(WEZEL_XML_FLOTY);
			if (flota){
				if (!XmlBO::ForEach<STACKTHROW>(flota, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
					Indeks identyfikator;
					XmlBO::WczytajAtrybut<STACKTHROW>(element, ATRYBUT_XML_IDENTYFIKATOR, identyfikator);
					auto wskaznik = std::make_shared<Flota>(identyfikator, STyp::Identyfikator(), STyp::Identyfikator(), Flota::CelPodrozy::Transport);
					auto iterator = listaFlot_.find(identyfikator);
					if (iterator != listaFlot_.end() || !wskaznik->odczytaj(element))
						return false;
					if (wskaznik->pobierzPlanetePoczatkowa() != identyfikator_)
						return false;
					Walidator::pobierzInstancje().dodajUzytyIdentyfikatorPlanety(wskaznik->pobierzPlanetePoczatkowa());
					Walidator::pobierzInstancje().dodajUzytyIdentyfikatorPlanety(wskaznik->pobierzPlaneteDocelowa());
					listaFlot_.insert(std::make_pair(wskaznik->pobierzIdentyfikator(), wskaznik));
					return true;
				}))){
					return false;
				}
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
		if (procentWody > Utils::FMAX || procentWody < Utils::FMIN ||
			procentUzytkowa > Utils::FMAX || procentUzytkowa < Utils::FMIN)
			return false;
		STyp::SPG::Powierzchnia calkowita = M_PI * srednicaPlanety_() * srednicaPlanety_();
		calkowitaPowierzchniaPlanety_(calkowita);
		powierzchniaZajetaPrzezWode_(calkowita * procentWody());
		powierzchniaLadow_(calkowita * (Utils::FMAX() - procentWody()));
		powierzchniaUzytkowaLadow_(powierzchniaLadow_() * procentUzytkowa());
		return true;
	}

	const STyp::Identyfikator& Planeta::pobierzIdentyfikator()const{
		return identyfikator_;
	}

	std::string Planeta::napis() const{
		SLog::Logger str(NAZWAKLASY(Planeta));
		str.dodajPole(NAZWAKLASY(Licznik), licznikIdentyfikatorowFloty_);
		str.dodajPole(NAZWAPOLA(odlegloscOdSlonca_), odlegloscOdSlonca_);
		//str.dodajPole("predkoscKatowaPlanety",predkoscKatowaPlanety_);
		//str.dodajPole("naslonecznieniePlanety",naslonecznieniePlanety_);
		str.dodajPole(NAZWAPOLA(idUkladu_), idUkladu_);
		str.dodajPole(NAZWAPOLA(temperaturaPlanety_), temperaturaPlanety_);
		str.dodajPole(NAZWAPOLA(calkowitaPowierzchniaPlanety_), calkowitaPowierzchniaPlanety_);
		str.dodajPole(NAZWAPOLA(powierzchniaZajetaPrzezWode_), powierzchniaZajetaPrzezWode_);
		str.dodajPole(NAZWAPOLA(powierzchniaLadow_), powierzchniaLadow_);
		str.dodajPole(NAZWAPOLA(powierzchniaUzytkowaLadow_), powierzchniaUzytkowaLadow_);
		str.dodajPole(NAZWAPOLA(nazwaPlanety_), nazwaPlanety_);
		/* Nie u¿ywana funkcjonalnoœæ
		for( auto element : dostepneZasobyPlanety_ )
			str.dodajPole("Zasob", element.second);
			*/
		for (auto element : listaObiektow_)
			str.dodajPole("Obiekt", *(element.second));
		for (auto element : listaFlot_)
			str.dodajPole("Flota", *(element.second));
		return str.napis();
	}
}
