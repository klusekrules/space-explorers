#include "BudynekInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"
#include "LiczenieKosztow.h"

BudynekInfo::BudynekInfo( TiXmlElement* wezel )
	: ObiektInfo(wezel)
{
	auto zapotrzebowanie = XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_ZAPOTRZEBOWANIE);
	while(zapotrzebowanie){
		zapotrzebowanie_.push_back(Cena(zapotrzebowanie,WEZEL_XML_SUROWCE));
		zapotrzebowanie = zapotrzebowanie->NextSiblingElement();
	}

	auto produkcja = XmlBO::ZnajdzWezel<NOTHROW>(wezel,WEZEL_XML_PRODUKCJA);
	while(produkcja){
		produkcja_.push_back( Cena(produkcja,WEZEL_XML_SUROWCE) );
		produkcja = produkcja->NextSiblingElement();
	}
}

bool BudynekInfo::tworz( const Gra& gra, Planeta& planeta , const Ilosc& ilosc ) const{
	return gra.wybudujNaPlanecie(planeta,*this,ilosc);
}

BudynekInfo::~BudynekInfo(){
}

Budynek* BudynekInfo::tworzEgzemplarz( const Ilosc& ilosc, const Identyfikator& identyfikatorPlanety ) const{
	return new Budynek(pobierzPoziom(),identyfikatorPlanety,*this);
}

Wymagania::PrzetworzonaCena BudynekInfo::PobierzZapotrzebowanie( const PodstawoweParametry& parametry )const{
	PrzetworzonaCena zbiornik;
	for( auto element : zapotrzebowanie_ ){
		LiczenieKosztow (element,zbiornik,Ilosc(1),parametry)();
	}
	return zbiornik;
}

Wymagania::PrzetworzonaCena BudynekInfo::PobierzProdukcje( const PodstawoweParametry& parametry )const{
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
