#include "Licznik.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

Licznik::Licznik(const Identyfikator& id, const Ilosc& w)
	: Base(id), wartoscLicznika(w)
{
}

Licznik::Licznik(const Identyfikator& id)
	: Base(id), wartoscLicznika(0)
{
}

Licznik::Licznik()
	: Base(Identyfikator(-1)), wartoscLicznika(0)
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
	return Base::zapisz(n);
}

bool Licznik::odczytaj( TiXmlElement* n ){
	if(n && Base::odczytaj(n)){
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
	str.dodajKlase(Base::napis());
	return str.napis();
}
