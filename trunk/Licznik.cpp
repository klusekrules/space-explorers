#include "Licznik.h"
#include "Logger.h"
#include "Utils.h"
#include "DefinicjeWezlowXML.h"

Licznik::Licznik(const Identyfikator& identyfikator, const Ilosc& wartoscPoczatkowa)
	: Bazowa(identyfikator), wartoscLicznika_(wartoscPoczatkowa)
{
}

Licznik::Licznik(const Identyfikator& identyfikator)
	: Bazowa(identyfikator), wartoscLicznika_(0)
{
}

Licznik::Licznik()
	: Bazowa(Identyfikator(-1)), wartoscLicznika_(0)
{
}

Ilosc Licznik::operator()(){
	return wartoscLicznika_++;
}

Ilosc Licznik::pobierzWartosc()const{
	return wartoscLicznika_;
}

void Licznik::resetujWartosc(){
	wartoscLicznika_ = Ilosc(0);
}

void Licznik::ustawWartosc( const Ilosc& wartosc ){
	wartoscLicznika_ = wartosc;
}

bool Licznik::zapisz( TiXmlElement* wezel ) const{
	TiXmlElement* dziecko = new TiXmlElement(WEZEL_XML_LICZNIK);
	wezel->LinkEndChild( dziecko );
	dziecko->SetAttribute(ATRYBUT_XML_ILOSC,wartoscLicznika_.napis());
	return Bazowa::zapisz(dziecko);
}

bool Licznik::odczytaj( TiXmlElement* wezel ){
	if(wezel && Bazowa::odczytaj(wezel)){
		auto atrybut = wezel->Attribute(ATRYBUT_XML_ILOSC);
		if(!atrybut)
			return false;
		string napisAtrybutu = atrybut;
		Utils::trim(napisAtrybutu);
		if(napisAtrybutu.empty())
			return false;
		wartoscLicznika_(stold(napisAtrybutu));
		return true;
	}
	return false;
}

string Licznik::napis()const{
	Logger str(NAZWAKLASY(Licznik));
	str.dodajKlase(Bazowa::napis());
	str.dodajPole("WartoœæLicznika",wartoscLicznika_);
	return str.napis();
}
