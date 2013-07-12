#include "WyjatekParseraXML.h"
#include "Logger.h"


WyjatekParseraXML::~WyjatekParseraXML(){
}

WyjatekParseraXML::WyjatekParseraXML( const WyjatekParseraXML& a )
	: OgolnyWyjatek(a), powod(a.powod)
{
}

WyjatekParseraXML::WyjatekParseraXML( const Tekst& tPlik, const Ilosc& iLinia, const std::exception& ex, const Tekst& str)
	: OgolnyWyjatek( tPlik, iLinia, idWyjatekParseraXML, tytulWyjatekParseraXML, str.isEmpty() ? trescWyjatekParseraXML : str ), powod(ex.what())
{
}

const Tekst& WyjatekParseraXML::getPowod() const{
	return powod;
}
void WyjatekParseraXML::setPowod( const Tekst& powod ){
	this->powod = powod;
}

Tekst WyjatekParseraXML::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + powod + Tekst("\n");
}

string WyjatekParseraXML::toString() const{
	Logger str(NAZWAKLASY(WyjatekParseraXML));
	str.dodajKlase(OgolnyWyjatek::toString());
	str.dodajPole("Powod",powod);
	return str.toString();
}