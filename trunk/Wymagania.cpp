#include "Wymagania.h"
#include "Logger\Logger.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"

namespace SpEx{

	Wymagania::Wymagania(XmlBO::ElementWezla wezel)
	{
		XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_KRYTERIUM, XmlBO::OperacjaWezla([&](XmlBO::ElementWezla warunek)->bool{
			Warunek obiekt(warunek);
			auto identyfikator = obiekt.pobierzObiekt()->pobierzIdentyfikator();
			for (auto element : warunki_){
				if (element.pobierzObiekt()->pobierzIdentyfikator() == identyfikator)
					Utils::generujWyjatekBleduStruktury(warunek);
			}
			warunki_.push_back(obiekt);
			return true;
		}));

		zmianaCzasuBudowy_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, WEZEL_XML_CZAS));
	}
	
	STyp::Czas Wymagania::pobierzCzasBudowy(const PodstawoweParametry& parametry)const{
		STyp::Czas suma(0.0l);
		auto &gra = Aplikacja::pobierzInstancje().pobierzGre();
		for (auto element : warunki_){
			auto obiekt = element.pobierzObiekt();
			if (obiekt){
				auto idObiektu = obiekt->pobierzIdentyfikator();
				if (obiekt->typAtrybutu() == Kryterium::ILOSC ){
					auto &obiektInfo = gra.pobierzObiekt(idObiektu);
					if (obiektInfo.typ_ == Info::SUROWIEC){
						Kryterium::AtrybutKryterium atrybut = wylicz(element, parametry);
						PodstawoweParametry nowe(STyp::Ilosc(atrybut.ilosc), parametry.pobierzIdentyfikatorPlanety());
						suma += obiektInfo.pobierzCzasBudowy(nowe);
					}
				}
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
					if (!(planeta->pobierzPoziomObiektu(element.pobierzObiekt()->pobierzIdentyfikator()) >= atrybut.poziom))
						return false;
					break;
				case Kryterium::ILOSC:
					if (!(planeta->pobierzIloscObiektu(element.pobierzObiekt()->pobierzIdentyfikator()) >= atrybut.ilosc))
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
				zbiornik.emplace_back(std::make_shared<Wymagania::TypWarunku>(wylicz(element, parametry), element.pobierzObiekt()->typAtrybutu(), element.pobierzObiekt()->pobierzIdentyfikator()));
		}
		return std::move(zbiornik);
	}

	Kryterium::AtrybutKryterium Wymagania::wylicz(const Warunek& warunek, const PodstawoweParametry& parametry){
		Kryterium::AtrybutKryterium atrybut;
		auto obiekt = warunek.pobierzObiekt();
		auto zmiana = warunek.pobierzZmiane();
		switch (obiekt->typAtrybutu()){
		case Kryterium::POZIOM:
			atrybut.poziom = Utils::ObliczZmiane(zmiana, STyp::Poziom(obiekt->pobierzAtrybut().poziom), parametry)();
			break;
		case Kryterium::ILOSC:
			atrybut.ilosc = Utils::ObliczZmiane(zmiana, STyp::Ilosc(obiekt->pobierzAtrybut().ilosc), parametry)();
		}
		if (parametry.typAtrybutu() == PodstawoweParametry::ILOSC)
			atrybut.ilosc *= parametry.pobierzAtrybut().ilosc;
		return std::move(atrybut);
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
