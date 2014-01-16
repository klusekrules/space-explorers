#include "Obrona.h"
#include "ObronaInfo.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"

Obrona::Obrona( const Ilosc& ilosc, const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const ObronaInfo& obronaInfo )
	: PodstawoweParametry(poziom, identyfikatorPlanety), Obiekt( ilosc, poziom, identyfikatorPlanety, obronaInfo ), JednostkaAtakujaca(poziom,identyfikatorPlanety,obronaInfo),obronaInfo_(obronaInfo)
{
}

Obrona::Obrona( const Ilosc& ilosc, const PodstawoweParametry& podstawoweParametry, const ObronaInfo& obronaInfo )
	: PodstawoweParametry(podstawoweParametry), Obiekt( ilosc, podstawoweParametry, obronaInfo ), JednostkaAtakujaca(podstawoweParametry,obronaInfo), obronaInfo_(obronaInfo)
{
}

Obrona* Obrona::kopia() const{
	return new Obrona(*this);
}

Obrona::~Obrona(){
}
	
Obrazenia Obrona::pobierzAtak() const{
	return Obrazenia (JednostkaAtakujaca::pobierzAtak()() * ilosc_());
}

Obrona* Obrona::podziel( const Ilosc& ilosc ){
	if( ilosc_>ilosc ){
		Obrona* o = new Obrona( ilosc , pobierzPoziom(), pobierzIdentyfikatorPlanety(), obronaInfo_ );
		ilosc_-=ilosc;
		return o; 
	}
	return nullptr;
}

Obrazenia Obrona::pobierzPancerz() const{
	return Obrazenia (JednostkaAtakujaca::pobierzPancerz()() * ilosc_());
}

Obrazenia Obrona::pobierzOslone() const{
	return Obrazenia (JednostkaAtakujaca::pobierzOslone()() * ilosc_());
}

const ObronaInfo& Obrona::pobierzObronaInfo() const{
	return obronaInfo_;
}

bool Obrona::zapisz( tinyxml2::XMLElement* wezel ) const {
	tinyxml2::XMLElement* element = wezel->GetDocument()->NewElement(WEZEL_XML_OBRONA);
	wezel->LinkEndChild( element );
	return Obiekt::zapisz(element);
}

bool Obrona::odczytaj( tinyxml2::XMLElement* wezel ) {
	return Obiekt::odczytaj(wezel);
}

string Obrona::napis() const{
	Logger str(NAZWAKLASY(Obrona));
	str.dodajKlase(Obiekt::napis());
	str.dodajKlase(JednostkaAtakujaca::napis());
	str.dodajPole(NAZWAKLASY(ObronaInfo)+"ID",obronaInfo_.pobierzIdentyfikator());
	return str.napis();
}
