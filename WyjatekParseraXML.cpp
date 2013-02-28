#include "WyjatekParseraXML.h"
#include "Logger.h"

WyjatekParseraXML::WyjatekParseraXML( const Tekst& tPlik, const IdType& iLinia )
	: OgolnyWyjatek(tPlik, iLinia, idWyjatekParseraXML)
{
}

WyjatekParseraXML::~WyjatekParseraXML(){
}

WyjatekParseraXML::WyjatekParseraXML( const WyjatekParseraXML& a )
	: OgolnyWyjatek(a), powod(a.powod)
{
}

WyjatekParseraXML::WyjatekParseraXML( const Tekst& tPlik, const IdType& iLinia, const Tekst& str, const std::exception& ex)
	: OgolnyWyjatek( tPlik, iLinia, idWyjatekParseraXML, tytulWyjatekParseraXML, str ), powod(ex.what())
{
}

WyjatekParseraXML::WyjatekParseraXML( const Tekst& tPlik, const IdType& iLinia, const std::exception& ex )
	: OgolnyWyjatek( tPlik, iLinia, idWyjatekParseraXML, tytulWyjatekParseraXML, trescWyjatekParseraXML ), powod(ex.what())
{
}

Tekst WyjatekParseraXML::getPowod() const{
	return powod;
}
void WyjatekParseraXML::setPowod( const Tekst& powod ){
	this->powod = powod;
}

Tekst WyjatekParseraXML::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + powod + Tekst("\n");
}

string WyjatekParseraXML::toString() const{
	Logger str(LogWyjBibTICPP::className());
	str.addClass(OgolnyWyjatek::toString());
	str.addField("Powod",powod);
	return str.toString();
}