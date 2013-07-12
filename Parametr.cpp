#include "Parametr.h"
#include "Logger.h"
#include "Stale.h"

Parametr::Parametr()
	: BaseInterface(Stale::parametrDomyslny)
{
}

Parametr::Parametr( const type_name& t )
	: BaseInterface(t)
{
}

Parametr::Parametr( const Parametr& a )	
	: BaseInterface(a)
{
}

Parametr::~Parametr(){
}

Parametr& Parametr::operator=( const Parametr& p ){
	wartosc_=p.wartosc_;
	return *this;
}

string Parametr::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Parametr),wartosc_);
}