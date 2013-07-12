#include "Wymagania.h"
#include "Logger.h"
#include "XmlBO.h"

Wymagania::Wymagania( TiXmlElement* n  ) throw(WyjatekParseraXML)
	: Cennik( n ), Warunek( n )
{
}

bool Wymagania::czySpelniaWymagania( const Ilosc& i, const PodstawoweParametry& p ) const{
	return czySpelniaKoszty(i,p) && czySpelniaWarunki(p);
}

string Wymagania::napis() const{
	Logger str(NAZWAKLASY(Wymagania));
	str.dodajKlase(Cennik::napis());
	str.dodajKlase(Warunek::napis());
	return str.napis();
}