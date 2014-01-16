#include "Budynek.h"
#include "BudynekInfo.h"
#include "Logger.h"
#include "DefinicjeWezlowXML.h"

Budynek::Budynek(const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const BudynekInfo& obiektInfo)
	: PodstawoweParametry(poziom, identyfikatorPlanety), Obiekt( Ilosc(1), poziom, identyfikatorPlanety, obiektInfo ), budynekInfo_(obiektInfo)
{
}

Budynek::Budynek(const PodstawoweParametry& podstawoweParametry, const BudynekInfo& obiektInfo)
	: PodstawoweParametry(podstawoweParametry), Obiekt( Ilosc(1), podstawoweParametry, obiektInfo ), budynekInfo_(obiektInfo)
{
}

Budynek::~Budynek(void){
}

Budynek* Budynek::kopia() const{
	return new Budynek(*this,budynekInfo_);
}

Budynek* Budynek::podziel( const Ilosc& ilosc ){
	return nullptr;
}

bool Budynek::polacz( const ObiektBazowy& obiektbazowy) {
	return false;
}
	
bool Budynek::czyMoznaPolaczyc( const ObiektBazowy& obiektbazowy ) const{
	return false;
}

bool Budynek::czyMoznaPodzielic( const Ilosc& ilosc) const{
	return false;
}

void Budynek::wybuduj(const Ilosc& ilosc){
	wzrostPoziomu();
}

Wymagania::PrzetworzonaCena Budynek::pobierzZapotrzebowanie( )const{
	return budynekInfo_.pobierzZapotrzebowanie(*this);
}

Wymagania::PrzetworzonaCena Budynek::pobierzProdukcje( )const{
	return budynekInfo_.pobierzProdukcje(*this);
}

bool Budynek::zapisz( tinyxml2::XMLElement* wezel ) const {
	tinyxml2::XMLElement* element = wezel->GetDocument()->NewElement(WEZEL_XML_BUDYNEK);
	wezel->LinkEndChild(element);
	return Obiekt::zapisz(element);
}

bool Budynek::odczytaj (tinyxml2::XMLElement* wezel) {
	return Obiekt::odczytaj(wezel);
}

string Budynek::napis()const{
	Logger str(NAZWAKLASY(Budynek));
	str.dodajKlase(Obiekt::napis());
	str.dodajPole(NAZWAKLASY(BudynekInfo)+"ID",budynekInfo_.pobierzIdentyfikator());
	return str.napis();
}
