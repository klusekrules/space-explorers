#include "Technologia.h"
#include "TechnologiaInfo.h"
#include "DefinicjeWezlowXML.h"

Technologia::Technologia( const Poziom& p, const IdType& idP, const TechnologiaInfo& t)
	: PodstawoweParametry(p, idP),ObiektBase(Ilosc(1),p,idP,t), technologiaInfo(t)
{
}
Technologia::Technologia( const PodstawoweParametry& p, const TechnologiaInfo& t)
	: PodstawoweParametry(p),ObiektBase(Ilosc(1),p,t), technologiaInfo(t)
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

bool Technologia::Polacz( ObiektBase& obiektBase){
	return false;
}
	
bool Technologia::czyMoznaPolaczyc( const ObiektBase& obiektBase) const{
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
	return ObiektBase::zapisz(n);
}

bool Technologia::odczytaj( TiXmlElement* e ) {
	return ObiektBase::odczytaj(e);
}

string Technologia::toString() const{
	Logger str(NAZWAKLASY(Technologia));
	str.dodajKlase(ObiektBase::toString());
	str.dodajPole(NAZWAKLASY(TechnologiaInfo)+"ID",technologiaInfo.getId());
	return str.toString();
}

