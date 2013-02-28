#include "BrakMaski.h"
#include "Logger.h"

BrakMaski::BrakMaski( const Tekst& tPlik, const IdType& iLinia)
	: WyjatekParseraXML(tPlik, iLinia)
{
	this->setNumerWyjatku(idBrakMaski);
	this->setTytul(tytulBrakMaski);
	this->setTresc(trescBrakMaski);
}

BrakMaski::BrakMaski( const Tekst& tPlik, const IdType& iLinia, const Tekst& nazwa )
	: WyjatekParseraXML(tPlik, iLinia), nazwaMaski(nazwa)
{
	this->setNumerWyjatku(idBrakMaski);
	this->setTytul(tytulBrakMaski);
	this->setTresc(trescBrakMaski);
}

BrakMaski::BrakMaski( const BrakMaski& e )
	: WyjatekParseraXML(e), nazwaMaski(e.nazwaMaski)
{
}

BrakMaski::~BrakMaski(){
}

Tekst BrakMaski::getNazwaMaski() const{
	return nazwaMaski;
}

void BrakMaski::setNazwaMaski( const Tekst& nazwaMaski ){
	this->nazwaMaski = nazwaMaski;
}

Tekst BrakMaski::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + nazwaMaski + Tekst("\n");
}

string BrakMaski::toString() const{
	Logger str(LogBrakMaski::className());
	str.addClass(WyjatekParseraXML::toString());
	str.addField("Nazwa Maski",nazwaMaski);
	return str.toString();
}
