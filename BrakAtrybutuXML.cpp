#include "BrakAtrybutuXML.h"
#include "Logger.h"

BrakAtrybutuXML::BrakAtrybutuXML( const Tekst& tPlik, const Ilosc& iLinia, const Tekst& str )
	: WyjatekParseraXML( tPlik, iLinia, std::exception(), trescBrakAtrybutuXML ), atrybut(str)
{
	this->setNumerWyjatku(idBrakAtrybutuXML);
	this->setTytul(tytulBrakAtrybutuXML);
}

BrakAtrybutuXML::BrakAtrybutuXML( const BrakAtrybutuXML& e )
	: WyjatekParseraXML(e), atrybut(e.atrybut)
{
}

BrakAtrybutuXML::~BrakAtrybutuXML(){
}

const Tekst& BrakAtrybutuXML::getAtrybut() const{
	return atrybut;
}

void BrakAtrybutuXML::setAtrybut( const Tekst& atrybut ){
	this->atrybut = atrybut;
}

Tekst BrakAtrybutuXML::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + atrybut + Tekst("\n");
}

string BrakAtrybutuXML::napis() const{
	Logger str(NAZWAKLASY(BrakAtrybutuXML));	
	str.dodajKlase(WyjatekParseraXML::napis());
	str.dodajPole("Atrybut",atrybut);
	return str.napis();
}