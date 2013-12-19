#include "BudynekInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Aplikacja.h"
#include "definicjeWezlowXML.h"
#include "LiczenieKosztow.h"
using namespace std::placeholders;
BudynekInfo::BudynekInfo( tinyxml2::XMLElement* wezel )
	: ObiektInfo(wezel)
{
	auto zapotrzebowanie = XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_ZAPOTRZEBOWANIE);
	while(zapotrzebowanie){
		auto cena = Cena(zapotrzebowanie,WEZEL_XML_SUROWCE,std::bind(&Gra::tworzSurowce,&(Aplikacja::pobierzInstancje().pobierzGre()),_1));
		auto identyfikator = cena.pobierzObiekt()->pobierzIdentyfikator();
		for(auto element : zapotrzebowanie_ ){
			if(element.pobierzObiekt()->pobierzIdentyfikator() == identyfikator)
				Utils::generujWyjatekBleduStruktury(EXCEPTION_PLACE,zapotrzebowanie);
		}
		zapotrzebowanie_.push_back(cena);
		zapotrzebowanie = zapotrzebowanie->NextSiblingElement();
	}

	auto produkcja = XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_PRODUKCJA);
	while(produkcja){
		auto cena = Cena(produkcja,WEZEL_XML_SUROWCE,std::bind(&Gra::tworzSurowce,&(Aplikacja::pobierzInstancje().pobierzGre()),_1));
		auto identyfikator = cena.pobierzObiekt()->pobierzIdentyfikator();
		for(auto element : produkcja_ ){
			if(element.pobierzObiekt()->pobierzIdentyfikator() == identyfikator)
				Utils::generujWyjatekBleduStruktury(EXCEPTION_PLACE,produkcja);
		}
		produkcja_.push_back(cena);
		produkcja = produkcja->NextSiblingElement();
	}
}

bool BudynekInfo::tworz( const Gra& gra , Planeta& planeta , const Ilosc& ilosc, const Poziom& poziom ) const{
	return gra.wybudujNaPlanecie(planeta,*this,ilosc,poziom);
}

BudynekInfo::~BudynekInfo(){
}

Budynek* BudynekInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety, const Poziom& poziom ) const{
	return new Budynek(poziom,identyfikatorPlanety,*this);
}

Budynek* BudynekInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return tworzEgzemplarz(ilosc,identyfikatorPlanety,pobierzPoziom() );
}

Wymagania::PrzetworzonaCena BudynekInfo::pobierzZapotrzebowanie( const PodstawoweParametry& parametry )const{
	PrzetworzonaCena zbiornik;
	for( auto element : zapotrzebowanie_ ){
		LiczenieKosztow (element,zbiornik,Ilosc(1),parametry)();
	}
	return zbiornik;
}

Wymagania::PrzetworzonaCena BudynekInfo::pobierzProdukcje( const PodstawoweParametry& parametry )const{
	PrzetworzonaCena zbiornik;
	for( auto element : produkcja_ ){
		LiczenieKosztow (element,zbiornik,Ilosc(1),parametry)();
	}
	return zbiornik;
}

string BudynekInfo::napis()const{
	Logger str(NAZWAKLASY(BudynekInfo));
	str.dodajKlase(ObiektInfo::napis());
	for(auto element : zapotrzebowanie_){
		str.rozpocznijPodKlase("Zapotrzebowanie");
		if(element.pobierzObiekt())
			str.dodajPole("Obiekt",*element.pobierzObiekt());
		if(element.pobierzZmiane())
			str.dodajPole("Zmiana",*element.pobierzZmiane());
		str.zakonczPodKlase();
	}
	for(auto element : produkcja_){
		str.rozpocznijPodKlase("Produkcja");
		if(element.pobierzObiekt())
			str.dodajPole("Obiekt",*element.pobierzObiekt());
		if(element.pobierzZmiane())
			str.dodajPole("Zmiana",*element.pobierzZmiane());
		str.zakonczPodKlase();
	}
	return str.napis();
}
