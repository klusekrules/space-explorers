#include "Parametr.h"
#include "../Logger/Logger.h"
#include "Stale.h"

Parametr::Parametr()
	: parametr(Stale::parametrDomyslny)
{
}

Parametr::Parametr( const type_name& t )
	: parametr(t)
{
}

Parametr::Parametr( const Parametr& a )	
	: parametr(a.parametr)
{
}

Parametr::~Parametr(){
}

Parametr& Parametr::operator=( const Parametr& p ){
	parametr=p.parametr;
	return *this;
}

void Parametr::setParametr( const type_name& t ){
	parametr = t;
}

Parametr::type_name Parametr::value() const{
	return parametr;
}

string Parametr::toString() const{
	return Logger::field(CLASSNAME(Parametr),parametr);
}