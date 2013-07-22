#include "Technologia.h"
#include "TechnologiaInfo.h"
#include "DefinicjeWezlowXML.h"

Technologia::Technologia( const Poziom& p, const Identyfikator& idP, const TechnologiaInfo& t)
	: PodstawoweParametry(p, idP),ObiektBazowy(Ilosc(1),p,idP,t), technologiaInfo(t)
{
}
Technologia::Technologia( const PodstawoweParametry& p, const TechnologiaInfo& t)
	: PodstawoweParametry(p),ObiektBazowy(Ilosc(1),p,t), technologiaInfo(t)
{
}
Technologia::~Technologia(void)
{
}

Technologia* Technologia::Kopia() const{
	return new Technologia(*this,technologiaInfo);
}

Technologia* Technologia::Podziel( const Ilosc& ilosc){
	return nullptr;
}

bool Technologia::Polacz( const ObiektBazowy& obiektBase){
	return false;
}
	
bool Technologia::czyMoznaPolaczyc( const ObiektBazowy& obiektBase) const{
	return false;
}

bool Technologia::czyMoznaPodzielic( const Ilosc& ilosc) const{
	return false;
}

void Technologia::wybuduj(const Ilosc&){
	wzrostPoziomu();
}

bool Technologia::zapisz( TiXmlElement* e ) const {
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_TECHNOLOGIA);
	e->LinkEndChild( n );
	return ObiektBazowy::zapisz(n);
}

bool Technologia::odczytaj( TiXmlElement* e ) {
	return ObiektBazowy::odczytaj(e);
}

string Technologia::napis() const{
	Logger str(NAZWAKLASY(Technologia));
	str.dodajKlase(ObiektBazowy::napis());
	str.dodajPole(NAZWAKLASY(TechnologiaInfo)+"ID",technologiaInfo.pobierzIdentyfikator());
	return str.napis();
}

