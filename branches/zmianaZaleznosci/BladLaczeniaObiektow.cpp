#include "BladLaczeniaObiektow.h"
#include "Logger.h"

BladLaczeniaObiektow::BladLaczeniaObiektow( const Tekst& tPlik, const Ilosc& iLinia, const Tekst& a , const Tekst& b )
	: OgolnyWyjatek( tPlik, iLinia, idBladLaczeniaObiektow, tytulBladLaczeniaObiektow, trescBladLaczeniaObiektow), obiektA(a), obiektB(b)
{
}

BladLaczeniaObiektow::~BladLaczeniaObiektow(){
}

const Tekst& BladLaczeniaObiektow::getObiektA() const{
	return obiektA;
}

void BladLaczeniaObiektow::setObiektA( const Tekst& a ){
	obiektA = a;
}

const Tekst& BladLaczeniaObiektow::getObiektB() const{
	return obiektB;
}

void BladLaczeniaObiektow::setObiektB( const Tekst& b ){
	obiektB = b;
}

Tekst BladLaczeniaObiektow::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("ObiektA:") +  obiektA  + Tekst("\nObiektB:") +  obiektB + Tekst("\n");
}

std::string BladLaczeniaObiektow::napis() const{
	Logger str(NAZWAKLASY(BladLaczeniaObiektow));	
	str.dodajKlase(OgolnyWyjatek::napis());
	str.dodajPole("ObiektA",obiektA);
	str.dodajPole("ObiektA",obiektB);
	return str.napis();
}