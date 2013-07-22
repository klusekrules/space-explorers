#include "Licznik.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

Licznik::Licznik(const Identyfikator& id, const Ilosc& w)
	: Bazowa(id), wartoscLicznika(w)
{
}

Licznik::Licznik(const Identyfikator& id)
	: Bazowa(id), wartoscLicznika(0)
{
}

Licznik::Licznik()
	: Bazowa(Identyfikator(-1)), wartoscLicznika(0)
{
}

Licznik::~Licznik(void)
{
}

Ilosc Licznik::operator()(){
	return wartoscLicznika++;
}

Ilosc Licznik::pobierzWartosc()const{
	return wartoscLicznika;
}

void Licznik::resetujWartosc(){
	wartoscLicznika = Ilosc(0);
}

void Licznik::ustawWartosc( const Ilosc& w ){
	wartoscLicznika = w;
}

bool Licznik::zapisz( TiXmlElement* e ) const{
	TiXmlElement* n = new TiXmlElement(WEZEL_XML_LICZNIK);
	e->LinkEndChild( n );
	n->SetAttribute(ATRYBUT_XML_ILOSC,wartoscLicznika.napis());
	return Bazowa::zapisz(n);
}

bool Licznik::odczytaj( TiXmlElement* n ){
	if(n && Bazowa::odczytaj(n)){
		string c = n->Attribute(ATRYBUT_XML_ILOSC);
		if(c.empty())
			return false;
		Utils::trim(c);
		wartoscLicznika(stold(c));
		return true;
	}
	return false;
}

string Licznik::napis()const{
	Logger str(NAZWAKLASY(Licznik));
	str.dodajKlase(Bazowa::napis());
	return str.napis();
}
