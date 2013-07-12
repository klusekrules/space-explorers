#include "NiezgodnyTypSurowca.h"
#include "Logger.h"

NiezgodnyTypSurowca::NiezgodnyTypSurowca( const Tekst& tPlik, const Ilosc& iLinia, const Klucz & tsP, const Klucz & tsD )
	: OgolnyWyjatek (  tPlik, iLinia, idNiezgodnyTypSurowca , tytulNiezgodnyTypSurowcaDomyslny , Tekst() )
{
	stringstream str;
	str<<"Brak zgodnosci typow. Uzyte typy = [ID Pierwszy = " << tsP().first.napis() << ", Poziom = "<< tsP().second.napis() << " ], [ID Drugi = "<< tsD().first.napis()<< ", Poziom = "<< tsD().second.napis() <<" ].";
	setTresc(str.str());
}

NiezgodnyTypSurowca::NiezgodnyTypSurowca( const NiezgodnyTypSurowca& wyjatek )
	: OgolnyWyjatek( wyjatek )
{
}

NiezgodnyTypSurowca::~NiezgodnyTypSurowca(){
}

string NiezgodnyTypSurowca::napis() const{
	Logger str(NAZWAKLASY(NiezgodnyTypSurowca));
	str.dodajKlase(OgolnyWyjatek::napis());
	return str.napis();
}