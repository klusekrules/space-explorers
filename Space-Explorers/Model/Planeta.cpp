#define _USE_MATH_DEFINES
#include "Planeta.h"
#include "Kontroler\Aplikacja.h"
#include "Utils\Utils.h"
#include "Utils\DefinicjeWezlowXML.h"
#include <functional>
#include "Uzytkownik.h"
#include "Kontroler\Gra.h"
#include "Kontroler\Zarzadca\ZarzadcaLokacji.h"
#include "Utils\StackThrow.h"

namespace SpEx{

	std::string Planeta::pobierzDebugInfo() const{
		return std::move(Utils::pobierzDebugInfo());
	}
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
		bool rezultat = false;
		if (wlasciciel_){
			rezultat = wlasciciel_->odpinaniePlanet(identyfikator_);
		}else{ 
			if (!idUzytkownika_.isEmpty()){
				wyczyscZawartoscPlanety();
				rezultat = true;
			} 
		}
		
		if (rezultat)
			SpEx::Aplikacja::pobierzInstancje().pobierzZarzadceLokacji().anulujRezerwacjePlanety(identyfikator_);

		return rezultat;
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

	bool Planeta::wybuduj(const Indeks& identyfikator, const PodstawoweParametry& ilosc){
		auto iterator = listaObiektow_.find(identyfikator);
		if (iterator != listaObiektow_.end()){
			iterator->second->wybuduj(ilosc);
			return true;
		}
		else{
			auto info = Aplikacja::pobierzInstancje().pobierzGre().pobierzObiektInfoJesliIstnieje<SpEx::ObiektInfo>(identyfikator);
			if (info)
				return info->tworz(*this, ilosc.pobierzAtrybut());
			return false;
		}
	}

	bool Planeta::wybuduj(const Indeks& identyfikator, const XmlBO::ElementWezla element){
		auto iterator = listaObiektow_.find(identyfikator);
		if (iterator != listaObiektow_.end()){
			return false;
		}else{
			auto info = Aplikacja::pobierzInstancje().pobierzGre().pobierzObiektInfoJesliIstnieje<SpEx::ObiektInfo>(identyfikator);
			if (info)
				return info->tworz(*this, element);
			return false;
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
	
	void Planeta::rozladujStatek(std::shared_ptr< Statek > statek){
		if (statek){
			for (auto element : statek->oproznijLadownie()){
				dodajObiekt<Surowce>(element.second);
			}
			for (auto element : statek->oproznijHangar()){
				dodajObiekt<Statek>(element.second);
			}
		}
	}

	bool Planeta::usunFlote(const Indeks& identyfikator){
		return listaFlot_.erase(identyfikator) != 0;
	}

	bool Planeta::zapisz(XmlBO::ElementWezla wezel) const{
		auto planeta = wezel->tworzElement(WEZEL_XML_PLANETA);
		planeta->tworzAtrybut(ATRYBUT_XML_ODLEGLOSC_OD_SLONCA, std::to_string(odlegloscOdSlonca_()).c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_SREDNICA, std::to_string(srednicaPlanety_()).c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR_RODZICA, std::to_string(idUkladu_()).c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_NAZWAGRACZA, idUzytkownika_().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_TEMPERATURA_PLANETY, std::to_string(temperaturaPlanety_()).c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_CALKOWITA_POWIERZNIA_PLANETY, std::to_string(calkowitaPowierzchniaPlanety_()).c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA_ZAJETA_PRZEZ_WODE, std::to_string(powierzchniaZajetaPrzezWode_()).c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA_LADOW, std::to_string(powierzchniaLadow_()).c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_POWIERZCHNIA_UZYTKOWA_LADOW, std::to_string(powierzchniaUzytkowaLadow_()).c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_NAZWA, nazwaPlanety_().c_str());
		planeta->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, std::to_string(identyfikator_()).c_str());
		licznikIdentyfikatorowFloty_.zapisz(planeta);
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
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_NAZWA, nazwaPlanety_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_ODLEGLOSC_OD_SLONCA, odlegloscOdSlonca_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_SREDNICA, srednicaPlanety_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_RODZICA, idUkladu_);
			XmlBO::WczytajAtrybut<NOTHROW>(wezel, ATRYBUT_XML_NAZWAGRACZA, idUzytkownika_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_TEMPERATURA_PLANETY, temperaturaPlanety_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_CALKOWITA_POWIERZNIA_PLANETY, calkowitaPowierzchniaPlanety_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_ZAJETA_PRZEZ_WODE, powierzchniaZajetaPrzezWode_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_LADOW, powierzchniaLadow_);
			XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA_UZYTKOWA_LADOW, powierzchniaUzytkowaLadow_);

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
				throw STyp::Wyjatek(EXCEPTION_PLACE, Utils::pobierzDebugInfo(), STyp::Identyfikator(145), STyp::Tekst("Niespójnoœæ danych!"),
					STyp::Tekst("Wykryto niespójnoœæ danych obiektów znajduj¹cych siê na planecie o id = " + std::to_string(identyfikator_())
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
		str.dodajPole(NAZWAPOLA(idUkladu_), idUkladu_);
		str.dodajPole(NAZWAPOLA(temperaturaPlanety_), temperaturaPlanety_);
		str.dodajPole(NAZWAPOLA(calkowitaPowierzchniaPlanety_), calkowitaPowierzchniaPlanety_);
		str.dodajPole(NAZWAPOLA(powierzchniaZajetaPrzezWode_), powierzchniaZajetaPrzezWode_);
		str.dodajPole(NAZWAPOLA(powierzchniaLadow_), powierzchniaLadow_);
		str.dodajPole(NAZWAPOLA(powierzchniaUzytkowaLadow_), powierzchniaUzytkowaLadow_);
		str.dodajPole(NAZWAPOLA(nazwaPlanety_), nazwaPlanety_);
		for (auto element : listaObiektow_)
			str.dodajPole("Obiekt", *(element.second));
		for (auto element : listaFlot_)
			str.dodajPole("Flota", *(element.second));
		return str.napis();
	}
}
