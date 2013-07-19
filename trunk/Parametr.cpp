#include "Parametr.h"
#include "Logger.h"
#include "Stale.h"

Parametr::Parametr()
	: PodstawowyInterfejs(Stale::parametrDomyslny)
{
}

Parametr::Parametr( const type_name& wartosc )
	: PodstawowyInterfejs(wartosc)
{
}

Parametr::Parametr( const Parametr& wartosc )	
	: PodstawowyInterfejs(wartosc)
{
}

Parametr::~Parametr(){
}

Parametr& Parametr::operator=( const Parametr& wartosc ){
	wartosc_=wartosc.wartosc_;
	return *this;
}

string Parametr::napis() const{
	return Logger::tworzPole(NAZWAKLASY(Parametr),wartosc_);
}
