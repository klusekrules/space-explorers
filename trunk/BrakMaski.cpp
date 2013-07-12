#include "BrakMaski.h"
#include "Logger.h"

BrakMaski::BrakMaski( const Tekst& tPlik, const Ilosc& iLinia, const Tekst& nazwa )
	: WyjatekParseraXML( tPlik, iLinia, exception(), trescBrakMaski ), nazwaMaski(nazwa)
{
	this->setNumerWyjatku(idBrakMaski);
	this->setTytul(tytulBrakMaski);
}

BrakMaski::BrakMaski( const BrakMaski& e )
	: WyjatekParseraXML(e), nazwaMaski(e.nazwaMaski)
{
}

BrakMaski::~BrakMaski(){
}

const Tekst& BrakMaski::getNazwaMaski() const{
	return nazwaMaski;
}

void BrakMaski::setNazwaMaski( const Tekst& nazwaMaski ){
	this->nazwaMaski = nazwaMaski;
}

Tekst BrakMaski::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + nazwaMaski + Tekst("\n");
}

string BrakMaski::napis() const{
	Logger str(NAZWAKLASY(BrakMaski));
	str.dodajKlase(WyjatekParseraXML::napis());
	str.dodajPole("Nazwa Maski",nazwaMaski);
	return str.napis();
}
