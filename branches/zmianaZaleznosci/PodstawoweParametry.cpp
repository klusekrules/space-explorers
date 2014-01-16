#include "PodstawoweParametry.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"
#include "XmlBO.h"
#include "Walidator.h"

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

bool PodstawoweParametry::zapisz( tinyxml2::XMLElement* wezel ) const{
	if( poziom_ <= Poziom(0) )
			return false;
	wezel->SetAttribute(ATRYBUT_XML_POZIOM,poziom_.napis().c_str());
	wezel->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETY,identyfikatorPlanety_.napis().c_str());
	return true;
}

bool PodstawoweParametry::odczytaj( tinyxml2::XMLElement* wezel ){
	if(wezel){
		int opcja = XmlBO::WczytajAtrybut<int>(wezel,ATRYBUT_XML_OPCJA,0);
		if(opcja == 1)
			return true;
		if(!XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_POZIOM,poziom_))
			return false;
		if( poziom_ <= Poziom(0) )
			return false;
		if(XmlBO::WczytajAtrybut<NOTHROW>(wezel,ATRYBUT_XML_IDENTYFIKATOR_PLANETY,identyfikatorPlanety_))
			Walidator::pobierzInstancje().dodajUzytyIdentyfikatorPlanety(identyfikatorPlanety_);
		else
			return false;
		return true;
	}
	return false;
}

string PodstawoweParametry::napis() const{
	Logger str(NAZWAKLASY(PodstawoweParametry));
	str.dodajPole(NAZWAKLASY(Poziom),poziom_);
	str.dodajPole(NAZWAKLASY(Identyfikator),identyfikatorPlanety_);
	return str.napis();
}
