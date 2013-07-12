#include "BladDzieleniaLadowni.h"

#include "Logger.h"

BladDzieleniaLadowni::BladDzieleniaLadowni( const Tekst& tPlik, const Ilosc& iLinia, const Tekst& tLadownia )
	: OgolnyWyjatek( tPlik, iLinia, idBladDzieleniaLadowni, tytulBladDzieleniaLadowni, trescBladDzieleniaLadowni ), ladownia( tLadownia )
{
}

BladDzieleniaLadowni::~BladDzieleniaLadowni(void){
}

Tekst BladDzieleniaLadowni::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("Ladownia:")  + ladownia + Tekst("\n");
}

const Tekst& BladDzieleniaLadowni::getLadownia() const{
	return ladownia;
}

void BladDzieleniaLadowni::setLadownia ( const Tekst& tLadownia ){
	ladownia = tLadownia;
}

string BladDzieleniaLadowni::napis() const{
	Logger str(NAZWAKLASY(BladDzieleniaLadowni));
	str.dodajKlase(OgolnyWyjatek::napis());
	str.dodajPole("Ladownia",ladownia);
	return str.napis();
}
