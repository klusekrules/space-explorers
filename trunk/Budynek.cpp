#include "Budynek.h"
#include "BudynekInfo.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"

Budynek::Budynek(const Poziom& p, const Identyfikator& idP, const BudynekInfo& o)
	: PodstawoweParametry(p, idP), Obiekt( Ilosc(1), p, idP, o ), budynekInfo(o)
{
}

Budynek::Budynek(const PodstawoweParametry& p, const BudynekInfo& o)
	: PodstawoweParametry(p), Obiekt( Ilosc(1), p, o ), budynekInfo(o)
{
}

Budynek* Budynek::Kopia() const{
	return new Budynek(*this,budynekInfo);
}

Budynek* Budynek::Podziel( const Ilosc& ilosc){
	return nullptr;
}

bool Budynek::Polacz( const ObiektBazowy& obiektBase){
	return false;
}
	
bool Budynek::czyMoznaPolaczyc( const ObiektBazowy& obiektBase) const{
	return false;
}

bool Budynek::czyMoznaPodzielic( const Ilosc& ilosc) const{
	return false;
}

void Budynek::wybuduj(const Ilosc&){
	wzrostPoziomu();
}

Budynek::~Budynek(void)
{
}

Wymagania::PrzetworzonaCena Budynek::PobierzZapotrzebowanie( )const{
	return budynekInfo.PobierzZapotrzebowanie(*this);
}

Wymagania::PrzetworzonaCena Budynek::PobierzProdukcje( )const{
	return budynekInfo.PobierzProdukcje(*this);
}

bool Budynek::zapisz( TiXmlElement* e ) const {
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_BUDYNEK);
	e->LinkEndChild( n );
	return Obiekt::zapisz(n);
}

bool Budynek::odczytaj (TiXmlElement* e) {
	return Obiekt::odczytaj(e);
}

string Budynek::napis()const{
	Logger str(NAZWAKLASY(Budynek));
	str.dodajKlase(Obiekt::napis());
	str.dodajPole(NAZWAKLASY(BudynekInfo)+"ID",budynekInfo.pobierzIdentyfikator());
	return str.napis();
}