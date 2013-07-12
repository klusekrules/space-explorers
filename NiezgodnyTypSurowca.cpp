#include "NiezgodnyTypSurowca.h"
#include "Logger.h"

NiezgodnyTypSurowca::NiezgodnyTypSurowca( const Tekst& tPlik, const Ilosc& iLinia, const Klucz & tsP, const Klucz & tsD )
	: OgolnyWyjatek (  tPlik, iLinia, idNiezgodnyTypSurowca , tytulNiezgodnyTypSurowcaDomyslny , Tekst() )
{
	stringstream str;
	str<<"Brak zgodnosci typow. Uzyte typy = [ID Pierwszy = " << tsP().first.toString() << ", Poziom = "<< tsP().second.toString() << " ], [ID Drugi = "<< tsD().first.toString()<< ", Poziom = "<< tsD().second.toString() <<" ].";
	setTresc(str.str());
}

NiezgodnyTypSurowca::NiezgodnyTypSurowca( const NiezgodnyTypSurowca& wyjatek )
	: OgolnyWyjatek( wyjatek )
{
}

NiezgodnyTypSurowca::~NiezgodnyTypSurowca(){
}

string NiezgodnyTypSurowca::toString() const{
	Logger str(NAZWAKLASY(NiezgodnyTypSurowca));
	str.dodajKlase(OgolnyWyjatek::toString());
	return str.toString();
}