#include "SygnaturaPlanety.h"
#include "Logger\Logger.h"
#include "XmlBO.h"
#include "definicjeWezlowXML.h"

SygnaturaPlanety::SygnaturaPlanety()
	: Bazowa(Identyfikator())
{
}

SygnaturaPlanety::SygnaturaPlanety( const Identyfikator& id , const Tekst& nazwaPlanety, const Tekst& nazwaGracza )
	:Bazowa(id), nazwaGracza_(nazwaGracza), nazwaPlanety_(nazwaPlanety)
{
}

SygnaturaPlanety::~SygnaturaPlanety()
{
}

Tekst SygnaturaPlanety::pobierzNazwePlanety()const{
	return nazwaPlanety_;
}

void SygnaturaPlanety::ustawNazwePlanety( const Tekst& nazwa ){
	nazwaPlanety_ = nazwa;
}

Tekst SygnaturaPlanety::pobierzNazweGracza()const{
	return nazwaGracza_;
}

void SygnaturaPlanety::ustawNazweGracza( const Tekst& nazwa ){
	nazwaGracza_ = nazwa;
}

bool SygnaturaPlanety::zapisz( TiXmlElement* wezel ) const{
	TiXmlElement* element = new TiXmlElement(WEZEL_XML_SYGNATURA_PLANETY);
	element->SetAttribute(ATRYBUT_XML_NAZWAGRACZA,nazwaGracza_());
	element->SetAttribute(ATRYBUT_XML_NAZWA,nazwaPlanety_());
	if(Bazowa::zapisz(element)){
		wezel->LinkEndChild(element);
		return true;
	}
	return false;
}

bool SygnaturaPlanety::odczytaj( TiXmlElement* wezel ) {
	if(wezel){		
		XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NAZWAGRACZA,nazwaGracza_);
		XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_NAZWA,nazwaPlanety_);
		return Bazowa::odczytaj(wezel);
	}
	return false;
}

string SygnaturaPlanety::napis() const{
	Logger str(NAZWAKLASY(SygnaturaPlanety));
	str.dodajKlase(Bazowa::napis());
	str.dodajPole("NazwaPlanety",nazwaPlanety_);
	str.dodajPole("NazwaGracza",nazwaGracza_);
	return str.napis();
}
