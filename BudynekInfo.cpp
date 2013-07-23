#include "BudynekInfo.h"
#include "Logger.h"
#include "XmlBO.h"
#include "Gra.h"
#include "definicjeWezlowXML.h"
#include "LiczenieKosztow.h"

BudynekInfo::BudynekInfo( TiXmlElement* n )
	: ObiektInfo(n)
{
	auto z = XmlBO::ZnajdzWezel<NOTHROW>(n,WEZEL_XML_ZAPOTRZEBOWANIE);
	while(z){
		zapotrzebowanie.push_back(Cena(z,WEZEL_XML_SUROWCE));
		z = z->NextSiblingElement();
	}

	auto p = XmlBO::ZnajdzWezel<NOTHROW>(n,WEZEL_XML_PRODUKCJA);
	while(p){
		produkcja.push_back( Cena(p,WEZEL_XML_SUROWCE) );
		p = p->NextSiblingElement();
	}
}

bool BudynekInfo::tworz( const Gra& g, Planeta& p , const Ilosc& i ) const{
	return g.wybudujNaPlanecie(p,*this,i);
}

BudynekInfo::~BudynekInfo(void)
{
}

Budynek* BudynekInfo::tworzEgzemplarz( const Ilosc&, const Identyfikator& idP ) const{
	return new Budynek(pobierzPoziom(),idP,*this);
}

Wymagania::PrzetworzonaCena BudynekInfo::PobierzZapotrzebowanie( const PodstawoweParametry& p )const{
	PrzetworzonaCena zb;
	for( auto e : zapotrzebowanie ){
		LiczenieKosztow (e,zb,Ilosc(1),p)();
	}
	return zb;
}

Wymagania::PrzetworzonaCena BudynekInfo::PobierzProdukcje( const PodstawoweParametry& p )const{
	PrzetworzonaCena zb;
	for( auto e : produkcja ){
		LiczenieKosztow (e,zb,Ilosc(1),p)();
	}
	return zb;
}

string BudynekInfo::napis()const{
	Logger str(NAZWAKLASY(BudynekInfo));
	str.dodajKlase(ObiektInfo::napis());
	for(auto element : zapotrzebowanie){
		str.rozpocznijPodKlase("Zapotrzebowanie");
		if(element.pobierzObiekt())
			str.dodajPole("Obiekt",*element.pobierzObiekt());
		if(element.pobierzZmiane())
			str.dodajPole("Zmiana",*element.pobierzZmiane());
		str.zakonczPodKlase();
	}
	for(auto element : produkcja){
		str.rozpocznijPodKlase("Produkcja");
		if(element.pobierzObiekt())
			str.dodajPole("Obiekt",*element.pobierzObiekt());
		if(element.pobierzZmiane())
			str.dodajPole("Zmiana",*element.pobierzZmiane());
		str.zakonczPodKlase();
	}
	return str.napis();
}