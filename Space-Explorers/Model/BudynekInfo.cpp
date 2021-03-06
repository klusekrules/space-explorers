#include "BudynekInfo.h"
#include "Planeta.h"
#include "Utils\DefinicjeWezlowXML.h"
#include "Utils\Utils.h"
#include "Utils\StackThrow.h"

namespace SpEx{

	BudynekInfo::BudynekInfo(XmlBO::ElementWezla wezel)
		: ObiektInfo(BUDYNEK, typAtrybutu, wezel)
	{
		XmlBO::WczytajAtrybut<STACKTHROW>(wezel, ATRYBUT_XML_POWIERZCHNIA, powierzchnia_);
		zmianaPowierzchni_ = Utils::TworzZmiane(XmlBO::ZnajdzWezelJezeli<NOTHROW>(wezel, WEZEL_XML_ZMIANA, ATRYBUT_XML_FOR, ATRYBUT_XML_POWIERZCHNIA));
		auto zapotrzebowanie = std::ref(zapotrzebowanie_);
		XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_ZAPOTRZEBOWANIE, XmlBO::OperacjaWezla([&zapotrzebowanie](XmlBO::ElementWezla warunek)->bool{
			Warunek obiekt(warunek);
			auto identyfikator = obiekt.pobierzObiekt()->pobierzIdentyfikator();
			for (auto element : zapotrzebowanie.get()){
				if (element.pobierzObiekt()->pobierzIdentyfikator() == identyfikator)
					Utils::generujWyjatekBleduStruktury(warunek);
			}
			zapotrzebowanie.get().push_back(obiekt);
			return true;
		}));
		
		auto produkcja = std::ref(produkcja_);
		XmlBO::ForEach<STACKTHROW>(wezel, WEZEL_XML_PRODUKCJA, XmlBO::OperacjaWezla([&produkcja](XmlBO::ElementWezla warunek)->bool{
			Warunek obiekt(warunek);
			auto identyfikator = obiekt.pobierzObiekt()->pobierzIdentyfikator();
			for (auto element : produkcja.get()){
				if (element.pobierzObiekt()->pobierzIdentyfikator() == identyfikator)
					Utils::generujWyjatekBleduStruktury(warunek);
			}
			produkcja.get().push_back(obiekt);
			return true;
		}));
		
	}

	bool BudynekInfo::tworz(Planeta& planeta, const PodstawoweParametry::AtrybutPodstawowy& atrybut) const{
		return planeta.dodajObiekt<Budynek>(Budynek::SharedPtr(tworzEgzemplarz(PodstawoweParametry(atrybut, typAtrybutu_))));
	}

	bool BudynekInfo::tworz(Planeta& planeta, const XmlBO::ElementWezla& element) const{
		auto budynek = Budynek::SharedPtr(tworzEgzemplarz(PodstawoweParametry(PodstawoweParametry::AtrybutPodstawowy(), typAtrybutu_)));
		if (budynek && element){
			if (!budynek->odczytaj(element))
				return false;
			return planeta.dodajObiekt<Budynek>(budynek);
		}
		return false;
	}
	
	STyp::Powierzchnia BudynekInfo::pobierzPowierzchnie(const PodstawoweParametry& parametry)const{
		return Utils::ObliczZmiane(zmianaPowierzchni_, powierzchnia_, parametry);
	}

	Budynek* BudynekInfo::tworzEgzemplarz(const PodstawoweParametry& parametry) const{
		return new Budynek(parametry, *this);
	}
	
	Wymagania::PrzetworzoneWarunki BudynekInfo::pobierzZapotrzebowanie(const PodstawoweParametry& parametry)const{
		PrzetworzoneWarunki zbiornik;
		for (auto element : zapotrzebowanie_){
			zbiornik.emplace_back(std::make_shared<Wymagania::TypWarunku>(wylicz(element, parametry), element.pobierzObiekt()->typAtrybutu(), element.pobierzObiekt()->pobierzIdentyfikator()));
		}
		return zbiornik;
	}

	Wymagania::PrzetworzoneWarunki BudynekInfo::pobierzProdukcje(const PodstawoweParametry& parametry)const{
		PrzetworzoneWarunki zbiornik;
		for (auto element : produkcja_){
			zbiornik.emplace_back(std::make_shared<Wymagania::TypWarunku>(wylicz(element, parametry), element.pobierzObiekt()->typAtrybutu(), element.pobierzObiekt()->pobierzIdentyfikator()));
		}
		return zbiornik;
	}

	std::string BudynekInfo::napis()const{
		SLog::Logger str(NAZWAKLASY(BudynekInfo));
		str.dodajKlase(ObiektInfo::napis());
		for (auto element : zapotrzebowanie_){
			str.rozpocznijPodKlase("Zapotrzebowanie");
			if (element.pobierzObiekt())
				str.dodajPole("Obiekt", *element.pobierzObiekt());
			if (element.pobierzZmiane())
				str.dodajPole("Zmiana", *element.pobierzZmiane());
			str.zakonczPodKlase();
		}
		for (auto element : produkcja_){
			str.rozpocznijPodKlase("Produkcja");
			if (element.pobierzObiekt())
				str.dodajPole("Obiekt", *element.pobierzObiekt());
			if (element.pobierzZmiane())
				str.dodajPole("Zmiana", *element.pobierzZmiane());
			str.zakonczPodKlase();
		}
		return str.napis();
	}
}
