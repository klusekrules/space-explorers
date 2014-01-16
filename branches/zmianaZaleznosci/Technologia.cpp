#include "Technologia.h"
#include "TechnologiaInfo.h"
#include "DefinicjeWezlowXML.h"
#include "Logger\Logger.h"

Technologia::Technologia( const Poziom& poziom, const Identyfikator& identyfikatorPlanety, const TechnologiaInfo& technologiaInfo)
	: PodstawoweParametry(poziom, identyfikatorPlanety),ObiektBazowy(Ilosc(1),poziom,identyfikatorPlanety,technologiaInfo), technologiaInfo_(technologiaInfo)
{
}
Technologia::Technologia( const PodstawoweParametry& podstawoweParametry, const TechnologiaInfo& technologiaInfo)
	: PodstawoweParametry(podstawoweParametry),ObiektBazowy(Ilosc(1),podstawoweParametry,technologiaInfo), technologiaInfo_(technologiaInfo)
{
}
Technologia::~Technologia(void)
{
}

Technologia* Technologia::kopia() const{
	return new Technologia(*this,technologiaInfo_);
}

Technologia* Technologia::podziel( const Ilosc& ilosc){
	return nullptr;
}

bool Technologia::polacz( const ObiektBazowy& obiektBase){
	return false;
}
	
bool Technologia::czyMoznaPolaczyc( const ObiektBazowy& obiektBase) const{
	return false;
}

bool Technologia::czyMoznaPodzielic( const Ilosc& ilosc) const{
	return false;
}

void Technologia::wybuduj(const Ilosc& ilosc){
	wzrostPoziomu();
}

bool Technologia::zapisz( tinyxml2::XMLElement* wezel ) const {
	tinyxml2::XMLElement* element = wezel->GetDocument()->NewElement(WEZEL_XML_TECHNOLOGIA);
	wezel->LinkEndChild( element );
	return ObiektBazowy::zapisz(element);
}

bool Technologia::odczytaj( tinyxml2::XMLElement* wezel ) {
	return ObiektBazowy::odczytaj(wezel);
}

string Technologia::napis() const{
	Logger str(NAZWAKLASY(Technologia));
	str.dodajKlase(ObiektBazowy::napis());
	str.dodajPole(NAZWAKLASY(TechnologiaInfo)+"ID",technologiaInfo_.pobierzIdentyfikator());
	return str.napis();
}
