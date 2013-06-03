#include "Wymagania.h"
#include "Logger.h"
#include "XmlBO.h"

Wymagania::Wymagania( ticpp::Node* n  ) throw(WyjatekParseraXML)
	: Cennik( XmlBO::IterateChildren<NOTHROW>(n,CLASSNAME(Cennik)) ), Warunek( XmlBO::IterateChildren<NOTHROW>(n,CLASSNAME(Warunek)) )
{
}

bool Wymagania::czySpelniaWymagania( const Ilosc& i, const Poziom& p, const IdType& idPlanety ) const{
	return czySpelniaKoszty(i,p,idPlanety) && czySpelniaWarunki(idPlanety);
}

Wymagania::Wymagania( const Wymagania& w )
	: Cennik(w), Warunek(w)
{	
}

Wymagania& Wymagania::operator=( const Wymagania& w ){
	Cennik::operator=(w);
	Warunek::operator=(w);
	return *this;
}

Wymagania::~Wymagania(){
}

string Wymagania::toString() const{
	Logger str(CLASSNAME(Wymagania));
	str.addClass(Cennik::toString());
	str.addClass(Warunek::toString());
	return str.toString();
}