#include "BrakAtrybutuXML.h"
#include "Logger.h"

BrakAtrybutuXML::BrakAtrybutuXML( const Tekst& tPlik, const IdType& iLinia )
	:WyjatekParseraXML( tPlik, iLinia)
{
	this->setNumerWyjatku(idBrakAtrybutuXML);
	this->setTytul(tytulBrakAtrybutuXML);
	this->setTresc(trescBrakAtrybutuXML);
}

BrakAtrybutuXML::BrakAtrybutuXML( const Tekst& tPlik, const IdType& iLinia, const Tekst& str )
	: WyjatekParseraXML( tPlik, iLinia), atrybut(str)
{
	this->setNumerWyjatku(idBrakAtrybutuXML);
	this->setTytul(tytulBrakAtrybutuXML);
	this->setTresc(trescBrakAtrybutuXML);
}

BrakAtrybutuXML::BrakAtrybutuXML( const BrakAtrybutuXML& e )
	: WyjatekParseraXML(e), atrybut(e.atrybut)
{
}

BrakAtrybutuXML::~BrakAtrybutuXML(){
}

Tekst BrakAtrybutuXML::getAtrybut() const{
	return atrybut;
}

void BrakAtrybutuXML::setAtrybut( const Tekst& atrybut ){
	this->atrybut = atrybut;
}

Tekst BrakAtrybutuXML::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + atrybut + Tekst("\n");
}

string BrakAtrybutuXML::toString() const{
	Logger str(LogBrakAtrXML::className());	
	str.addClass(WyjatekParseraXML::toString());
	str.addField("Atrybut",atrybut);
	return str.toString();
}