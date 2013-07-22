#include "PodstawoweParametry.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

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
		auto atrybut = wezel->Attribute(ATRYBUT_XML_POZIOM);
		if(!atrybut)
			return false;
		string napisAtrybutu = atrybut;
		Utils::trim(napisAtrybutu);
		if(napisAtrybutu.empty())
			return false;
		poziom_(stoul(napisAtrybutu));
		napisAtrybutu.clear();
		atrybut = wezel->Attribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETY);
		if(!atrybut)
			return false;
		napisAtrybutu.append(atrybut);
		Utils::trim(napisAtrybutu);
		if(napisAtrybutu.empty())
			return false;	
		identyfikatorPlanety_(stoul(napisAtrybutu,nullptr,0));
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
