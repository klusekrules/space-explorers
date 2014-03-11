#include "Flota.h"
#include "Aplikacja.h"
#include "DefinicjeWezlowXML.h"
#include "Logger\Logger.h"

namespace SpEx{
	Flota::Flota(const STyp::Identyfikator& id, const STyp::Identyfikator& planetaPoczatkowa, const STyp::Identyfikator& planetaDocelowa, CelPodrozy celPodrozy)
		: idFloty_(id), planetaPoczatkowa_(planetaPoczatkowa), planetaDocelowa_(planetaDocelowa), celPodrozy_(celPodrozy)
	{
	}

	STyp::Identyfikator Flota::pobierzPlaneteDocelowa() const{
		return planetaDocelowa_;
	}

	STyp::Identyfikator Flota::pobierzPlanetePoczatkowa() const{
		return planetaPoczatkowa_;
	}

	const STyp::Identyfikator& Flota::pobierzIdentyfikator()const{
		return idFloty_;
	}

	bool Flota::dodajStatek(std::shared_ptr<Statek> statek){
		if (!statek)
			return false;
		auto iterator = lista_.find(statek->pobierzIdentyfikator());
		if (iterator == lista_.end()){
			statek->ustawIdentyfikatorPlanety(STyp::Identyfikator());
			lista_.insert(make_pair(statek->pobierzIdentyfikator(), statek));
		}
		else{
			return iterator->second->polacz(*statek);
		}
		return true;
	}

	bool Flota::dodajLadunek(std::shared_ptr<Surowce> obiekt){
		if (!obiekt)
			return false;
		STyp::Objetosc objetoscObiektu = obiekt->pobierzObjetosc();
		if (pobierzDostepneMiejsceLadowni() < objetoscObiektu)
			return false;
		STyp::Objetosc objetoscJednostkowa = obiekt->pobierzObjetoscJednostkowa();

		std::map<STyp::Objetosc, STyp::Identyfikator, std::less<STyp::Objetosc> > posortowane;
		for (auto element : lista_)
			posortowane.insert(std::make_pair(element.second->pobierzPojemnoscJednostkowaLadowni(), element.first));

		for (auto element : posortowane){
			if (element.first < objetoscJednostkowa)
				continue;
			auto iter = lista_.find(element.second);
			if (iter == lista_.end())
				continue;
			std::shared_ptr<Surowce> obiektDoDodania = obiekt;
			STyp::Objetosc dostepneMiejsce = iter->second->pobierzDostepneMiejsceLadowni();
			if (objetoscObiektu > dostepneMiejsce){
				STyp::Ilosc ilosc(floor(dostepneMiejsce() / objetoscJednostkowa()));
				obiektDoDodania = std::shared_ptr<Surowce>(obiekt->podziel(ilosc));
				if (iter->second->dodajObiektDoLadowni(obiektDoDodania))
					return true;
				else
					obiekt->polacz(*obiektDoDodania);
			}
			else{
				if (iter->second->dodajObiektDoLadowni(obiektDoDodania))
					return true;
			}
		}
		return false;
	}

	bool Flota::dodajLadunek(std::shared_ptr<Statek> obiekt){
		if (!obiekt)
			return false;
		STyp::Powierzchnia objetoscObiektu = obiekt->pobierzPowierzchnie();
		if (pobierzDostepneMiejsceHangaru() < objetoscObiektu)
			return false;
		STyp::Powierzchnia objetoscJednostkowa = obiekt->pobierzPowierzchnieJednostkowa();

		std::map<STyp::Powierzchnia, STyp::Identyfikator, std::less<STyp::Powierzchnia> > posortowane;
		for (auto element : lista_)
			posortowane.insert(std::make_pair(element.second->pobierzPojemnoscJednostkowaHangaru(), element.first));

		for (auto element : posortowane){
			if (element.first < objetoscJednostkowa)
				continue;
			auto iter = lista_.find(element.second);
			if (iter == lista_.end())
				continue;
			std::shared_ptr<Statek> obiektDoDodania = obiekt;
			STyp::Powierzchnia dostepneMiejsce = iter->second->pobierzDostepneMiejsceHangaru();
			if (objetoscObiektu > dostepneMiejsce){
				STyp::Ilosc ilosc(floor(dostepneMiejsce() / objetoscJednostkowa()));
				obiektDoDodania = std::shared_ptr<Statek>(obiekt->podziel(ilosc));
				if (iter->second->dodajStatekDoHangaru(obiektDoDodania))
					return true;
				else
					obiekt->polacz(*obiektDoDodania);
			}
			else{
				if (iter->second->dodajStatekDoHangaru(obiektDoDodania))
					return true;
			}
		}
		return false;
	}

	STyp::Objetosc Flota::pobierzDostepneMiejsceLadowni() const{
		STyp::Objetosc suma(0.0);
		for (auto element : lista_){
			suma += element.second->pobierzDostepneMiejsceLadowni();
		}
		return suma;
	}

	STyp::Powierzchnia Flota::pobierzDostepneMiejsceHangaru() const{
		STyp::Powierzchnia suma(0.0);
		for (auto element : lista_){
			suma += element.second->pobierzDostepneMiejsceHangaru();
		}
		return suma;
	}

	void Flota::ustawPlaneteDocelowa(const STyp::Identyfikator& identyfikatorPlanety){
		planetaDocelowa_ = identyfikatorPlanety;
	}

	void Flota::ustawPlanetePoczatkowa(const STyp::Identyfikator& identyfikatorPlanety){
		planetaPoczatkowa_ = identyfikatorPlanety;
	}

	void Flota::ustawCelPodrozy(CelPodrozy cel){
		celPodrozy_ = cel;
	}

	bool Flota::rozladujLadownieNaPlanecie(){
		std::shared_ptr<Planeta> planeta;
		try{
			switch (celPodrozy_){
			case Stacjonowanie:
			case Transport: planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(planetaDocelowa_);
				break;
			case Powrot: planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(planetaPoczatkowa_);
				break;
			case Zwiad:
			case Szczatki:
			case Ekspedycja:
			case Atak:
			default:
				return false;
			}
		}
		catch (NieznalezionoObiektu& e){
			return false;
		}
		if (!planeta)
			return false;
		for (auto statek : lista_)
			if (statek.second){
				planeta->rozladujStatek(statek.second);
			}
		return true;
	}

	bool Flota::rozladujFloteNaPlanecie(){
		std::shared_ptr<Planeta> planeta;
		try{
			switch (celPodrozy_){
			case Stacjonowanie:
			case Transport: planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(planetaDocelowa_);
				break;
			case Powrot: planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(planetaPoczatkowa_);
				break;
			case Zwiad:
			case Szczatki:
			case Ekspedycja:
			case Atak:
			default:
				return false;
			}
		}
		catch (NieznalezionoObiektu& e){
			return false;
		}
		if (!planeta)
			return false;
		for (auto statek : lista_)
			if (statek.second){
				planeta->rozladujStatek(statek.second);
				planeta->dodajObiekt(statek.second);
			}
		lista_.clear();
		return true;
	}

	bool Flota::zawrocFlote(){
		if (celPodrozy_ == Powrot)
			return false;
		celPodrozy_ = Powrot;
		return true;
	}

	bool Flota::zapisz(XmlBO::ElementWezla wezel) const{
		if (wezel){
			auto element = wezel->tworzElement(WEZEL_XML_FLOTA);
			element->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR, idFloty_.napis().c_str());
			element->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR_PLANETA_POCZATKOWA, planetaPoczatkowa_.napis().c_str());
			element->tworzAtrybut(ATRYBUT_XML_IDENTYFIKATOR_PLANETA_DOCELOWA, planetaDocelowa_.napis().c_str());
			element->tworzAtrybut(ATRYBUT_XML_CEL_PODROZY, "")->ustawWartoscInt(celPodrozy_);
			for (auto statek : lista_)
				if (statek.second)
					statek.second->zapisz(element);
			return true;
		}
		return false;
	}

	bool Flota::odczytaj(XmlBO::ElementWezla wezel) {
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR, idFloty_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_PLANETA_POCZATKOWA, planetaPoczatkowa_);
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_IDENTYFIKATOR_PLANETA_DOCELOWA, planetaDocelowa_);
		int cel;
		auto atrybut = wezel->pobierzAtrybut(ATRYBUT_XML_CEL_PODROZY);
		if (!atrybut && atrybut->operator bool())
			return false;
		cel = atrybut->pobierzWartoscInt();
		switch (cel){
		case Zwiad: celPodrozy_ = Zwiad;
			break;
		case Atak: celPodrozy_ = Atak;
			break;
		case Transport: celPodrozy_ = Transport;
			break;
		case Stacjonowanie: celPodrozy_ = Stacjonowanie;
			break;
		case Szczatki: celPodrozy_ = Szczatki;
			break;
		case Ekspedycja: celPodrozy_ = Ekspedycja;
			break;
		case Powrot: celPodrozy_ = Powrot;
			break;
		default:
			return false;
		}
		return XmlBO::ForEach<STACKTHROW>(wezel, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla element)->bool{
			STyp::Identyfikator identyfikator;
			XmlBO::WczytajAtrybut<STACKTHROW>(element, ATRYBUT_XML_IDENTYFIKATOR, identyfikator);
			PodstawoweParametry parametry(PodstawoweParametry::wpisIlosc(STyp::Ilosc()), PodstawoweParametry::ILOSC, STyp::Identyfikator());
			auto statek = std::shared_ptr<Statek>(Aplikacja::pobierzInstancje().pobierzGre().pobierzStatek(identyfikator).tworzEgzemplarz(parametry));
			if (!statek->odczytaj(element))
				return false;
			lista_.insert(make_pair(statek->pobierzIdentyfikator(), statek));
			return true;
		}));
	}

	std::string Flota::napis()const {
		SLog::Logger str(NAZWAKLASY(Ladownia));
		str.dodajPole(NAZWAPOLA(celPodrozy_), std::to_string(celPodrozy_));
		str.dodajPole(NAZWAPOLA(planetaDocelowa_), planetaDocelowa_);
		str.dodajPole(NAZWAPOLA(planetaPoczatkowa_), planetaPoczatkowa_);
		for (auto s : lista_)
			if (s.second)
				str.dodajPole(NAZWAPOLA(Statek), *s.second);
		return str.napis();
	}
}