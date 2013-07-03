#include "PodstawoweParametry.h"
#include "Logger.h"


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

string PodstawoweParametry::toString() const{
	Logger str(CLASSNAME(PodstawoweParametry));
	str.addField(CLASSNAME(Poziom),poziom);
	str.addField(CLASSNAME(IdType),idPlanety);
	return str.toString();
}