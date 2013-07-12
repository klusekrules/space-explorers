#include "Parametr.h"
#include "Logger.h"
#include "Stale.h"

Parametr::Parametr()
	: PodstawowyInterfejs(Stale::parametrDomyslny)
{
}

Parametr::Parametr( const type_name& t )
	: PodstawowyInterfejs(t)
{
}

Parametr::Parametr( const Parametr& a )	
	: PodstawowyInterfejs(a)
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