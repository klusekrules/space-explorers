#include "Wymagania.h"
#include "Logger.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

namespace SpEx{

	Wymagania::Wymagania(XmlBO::ElementWezla wezel)
	{
		auto warunki = std::ref(warunki_);
		XmlBO::ForEach<THROW>(wezel, WEZEL_XML_KRYTERIUM, XmlBO::OperacjaWezla([&warunki](XmlBO::ElementWezla warunek)->bool{
			Warunek obiekt(warunek);
			auto identyfikator = obiekt.pobierzObiekt()->pobierzIdentyfikator();
			for (auto element : warunki.get()){
				if (element.pobierzObiekt()->pobierzIdentyfikator() == identyfikator)
					SPar::ParserUtils::generujWyjatekBleduStruktury(warunek);
			}
			warunki.get().push_back(obiekt);
			return true;
		}));

		zmianaCzasuBudowy_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WEZEL_XML_CZAS));
	}
	
	STyp::Czas Wymagania::pobierzCzasBudowy(const PodstawoweParametry& parametry)const{
		STyp::Czas suma(0.0l);
		for (auto element : warunki_){
			if (element.pobierzObiekt() && element.pobierzObiekt()->typAtrybutu() == Kryterium::ILOSC)
			{
				Kryterium::AtrybutKryterium atrybut = wylicz(element, parametry);
				suma += 0.0l; //TODO: Pobranie planety, surowca info, wyliczenie czasu ze zmiany. Pobierz surowiec na planecie Wyliczanie czasu rozbudowy obiektu. atrybut.ilosc;
			}
		}
		return Utils::ObliczZmiane(zmianaCzasuBudowy_, suma, parametry);
	}

	bool Wymagania::czySpelniaWymagania(const PodstawoweParametry& parametry) const{
		//TODO: Zrobiæ schemat blokowy algorytmu sprawdzania spe³nienia warunków.
		if (warunki_.empty())
			return true;
		std::shared_ptr<Planeta> planeta = Aplikacja::pobierzInstancje().pobierzGre().pobierzPlanete(parametry.pobierzIdentyfikatorPlanety());
		if (!planeta){
			return false;
		}
		for (auto element : warunki_){
			if (element.pobierzObiekt())
			{
				Kryterium::AtrybutKryterium atrybut = wylicz(element, parametry);
				switch (element.pobierzObiekt()->typAtrybutu()){
				case Kryterium::POZIOM:
					if (planeta->pobierzIloscObiektu(element.pobierzObiekt()->pobierzIdentyfikator()) < atrybut.ilosc)
						return false;
					break;
				case Kryterium::ILOSC:
					if (planeta->pobierzPoziomObiektu(element.pobierzObiekt()->pobierzIdentyfikator()) < atrybut.poziom)
						return false;
					break;
				}
			}
		}
		return true;
	}

	Wymagania::PrzetworzoneWarunki Wymagania::pobierzWarunki(const PodstawoweParametry& parametry) const{
		PrzetworzoneWarunki zbiornik;
		for (auto element : warunki_){
			if (element.pobierzObiekt())
				zbiornik.emplace_back(wylicz(element, parametry), element.pobierzObiekt()->typAtrybutu(), element.pobierzObiekt()->pobierzIdentyfikator());
		}
		return zbiornik;
	}

	Kryterium::AtrybutKryterium Wymagania::wylicz(const Warunek& warunek, const PodstawoweParametry& parametry){
		Kryterium::AtrybutKryterium atrybut;
		auto obiekt = warunek.pobierzObiekt();
		auto zmiana = warunek.pobierzZmiane();
		switch (obiekt->typAtrybutu()){
		case Kryterium::POZIOM:
			atrybut.poziom = Utils::ObliczZmiane(zmiana, obiekt->pobierzAtrybut().poziom, parametry);
			break;
		case Kryterium::ILOSC:
			atrybut.ilosc = Utils::ObliczZmiane(zmiana, obiekt->pobierzAtrybut().ilosc, parametry);
		}
		if (parametry.typAtrybutu() == PodstawoweParametry::ILOSC)
			atrybut.ilosc *= parametry.pobierzAtrybut().ilosc;
		return atrybut;
	}

	std::string Wymagania::napis() const{
		SLog::Logger str(NAZWAKLASY(Wymagania));

		str.rozpocznijPodKlase(NAZWAKLASY(Wymagania::ListaWarunkow));
		for (auto element : warunki_){
			str.rozpocznijPodKlase(NAZWAKLASY(Wymagania::Warunek));
			if (element.pobierzObiekt())
				str.dodajPole("Obiekt", *element.pobierzObiekt());
			if (element.pobierzZmiane())
				str.dodajPole("Zmiana", *element.pobierzZmiane());
			str.zakonczPodKlase();
		}
		str.zakonczPodKlase();

		if (zmianaCzasuBudowy_)
			str.dodajPole(NAZWAPOLA(zmianaCzasuBudowy_), *zmianaCzasuBudowy_);

		return str.napis();
	}
}
