#include "PodstawoweParametry.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

PodstawoweParametry::PodstawoweParametry( const Poziom& poziom, const IdType& planeta)
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

const IdType& PodstawoweParametry::getIdPlanety() const{
	return idPlanety;
}

void PodstawoweParametry::setIdPlanety( const IdType& id ){
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
	e->SetAttribute(ATRYBUT_XML_POZIOM,poziom.toString());
	e->SetAttribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETY,idPlanety.toString());
	return true;
}

bool PodstawoweParametry::odczytaj( TiXmlElement* e ){
	if(e){
		string c = e->Attribute(ATRYBUT_XML_POZIOM);
		if(c.empty())
			return false;
		Utils::trim(c);
		poziom(stoul(c));

		c.clear();
		c.append(e->Attribute(ATRYBUT_XML_IDENTYFIKATOR_PLANETY));
		if(c.empty())
			return false;
		Utils::trim(c);		
		idPlanety(stoul(c,nullptr,0));
		return true;
	}
	return false;
}

string PodstawoweParametry::toString() const{
	Logger str(NAZWAKLASY(PodstawoweParametry));
	str.dodajPole(NAZWAKLASY(Poziom),poziom);
	str.dodajPole(NAZWAKLASY(IdType),idPlanety);
	return str.toString();
}