#include "Wymagania.h"
#include "Logger.h"
#include "XmlBO.h"

Wymagania::Wymagania( ticpp::Node* n  ) throw(WyjatekParseraXML)
	: Cennik( XmlBO::IterateChildren<NOTHROW>(n,CLASSNAME(Cennik)) ), Warunek( XmlBO::IterateChildren<NOTHROW>(n,CLASSNAME(Warunek)) )
{
}

bool Wymagania::czySpelniaWymagania( const Ilosc& i, const PodstawoweParametry& p ) const{
	return czySpelniaKoszty(i,p) && czySpelniaWarunki(p);
}

string Wymagania::toString() const{
	Logger str(CLASSNAME(Wymagania));
	str.addClass(Cennik::toString());
	str.addClass(Warunek::toString());
	return str.toString();
}