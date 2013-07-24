#include "PodstawoweParametry.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"

PodstawoweParametry::PodstawoweParametry( const Poziom& poziom, const Identyfikator& planeta)
	: poziom_(poziom), identyfikatorPlanety_(planeta)
{
}

const Poziom& PodstawoweParametry::pobierzPoziom() const{
	return poziom_;
}

void PodstawoweParametry::ustawPoziom( const Poziom& poziom ){
	poziom_=poziom;
}

const Identyfikator& PodstawoweParametry::pobierzIdentyfikatorPlanety() const{
	return identyfikatorPlanety_;
}

void PodstawoweParametry::ustawIdentyfikatorPlanety( const Identyfikator& identyfikatorPlanety ){
	identyfikatorPlanety_ = identyfikatorPlanety;
}

void PodstawoweParametry::ustawKontekst( const PodstawoweParametry& podstawoweParametry ){
	poziom_ = podstawoweParametry.poziom_;
	identyfikatorPlanety_ = podstawoweParametry.identyfikatorPlanety_;
}
void PodstawoweParametry::wzrostPoziomu(){
	++poziom_;
}

bool PodstawoweParametry::zapisz( TiXmlElement* wezel ) const{
	wezel->SetAttribute(ATRYBUT_XML_POZIOM,poziom_.napis());
	wezel->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETY,identyfikatorPlanety_.napis());
	return true;
}

bool PodstawoweParametry::odczytaj( TiXmlElement* wezel ){
	if(wezel){
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_POZIOM,poziom_))
			return false;
		return XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR_PLANETY,identyfikatorPlanety_);
	}
	return false;
}

string PodstawoweParametry::napis() const{
	Logger str(NAZWAKLASY(PodstawoweParametry));
	str.dodajPole(NAZWAKLASY(Poziom),poziom_);
	str.dodajPole(NAZWAKLASY(Identyfikator),identyfikatorPlanety_);
	return str.napis();
}
