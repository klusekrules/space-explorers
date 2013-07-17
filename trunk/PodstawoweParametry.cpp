#include "PodstawoweParametry.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

PodstawoweParametry::PodstawoweParametry( const Poziom& poziom, const Identyfikator& planeta)
	: poziom(poziom), idPlanety(planeta)
{
}

PodstawoweParametry::~PodstawoweParametry(void)
{
}

const Poziom& PodstawoweParametry::getPoziom() const{
	return poziom;
}

void PodstawoweParametry::setPoziom(const Poziom& p){
	poziom=p;
}

const Identyfikator& PodstawoweParametry::getIdPlanety() const{
	return idPlanety;
}

void PodstawoweParametry::setIdPlanety( const Identyfikator& id ){
	idPlanety = id;
}

void PodstawoweParametry::ustawKontekst( const PodstawoweParametry& p ){
	poziom = p.poziom;
	idPlanety = p.idPlanety;
}
void PodstawoweParametry::wzrostPoziomu(){
	++poziom;
}

bool PodstawoweParametry::zapisz( TiXmlElement* e ) const{
	e->SetAttribute(ATRYBUT_XML_POZIOM,poziom.napis());
	e->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETY,idPlanety.napis());
	return true;
}

bool PodstawoweParametry::odczytaj( TiXmlElement* e ){
	if(e){
		auto ptr = e->Attribute(ATRYBUT_XML_POZIOM);
		if(!ptr)
			return false;
		string c = ptr;
		Utils::trim(c);
		if(c.empty())
			return false;
		poziom(stoul(c));
		c.clear();
		ptr = e->Attribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETY);
		if(!ptr)
			return false;
		c.append(ptr);
		Utils::trim(c);
		if(c.empty())
			return false;	
		idPlanety(stoul(c,nullptr,0));
		return true;
	}
	return false;
}

string PodstawoweParametry::napis() const{
	Logger str(NAZWAKLASY(PodstawoweParametry));
	str.dodajPole(NAZWAKLASY(Poziom),poziom);
	str.dodajPole(NAZWAKLASY(Identyfikator),idPlanety);
	return str.napis();
}