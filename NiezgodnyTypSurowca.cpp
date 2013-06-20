#include "NiezgodnyTypSurowca.h"
#include "Logger.h"

NiezgodnyTypSurowca::NiezgodnyTypSurowca( const Tekst& tPlik, const Ilosc& iLinia, const Klucz & tsP, const Klucz & tsD )
	: OgolnyWyjatek (  tPlik, iLinia, idNiezgodnyTypSurowca , tytulNiezgodnyTypSurowcaDomyslny , Tekst() )
{
	stringstream str;
	str<<"Brak zgodnosci typow. Uzyte typy = [ID Pierwszy = " << tsP.getKlucz().first.toString() << ", Poziom = "<< tsP.getKlucz().second.toString() << " ], [ID Drugi = "<< tsD.getKlucz().first.toString()<< ", Poziom = "<< tsD.getKlucz().second.toString() <<" ].";
	setTresc(str.str());
}

NiezgodnyTypSurowca::NiezgodnyTypSurowca( const NiezgodnyTypSurowca& wyjatek )
	: OgolnyWyjatek( wyjatek )
{
}

NiezgodnyTypSurowca::~NiezgodnyTypSurowca(){
}

string NiezgodnyTypSurowca::toString() const{
	Logger str(CLASSNAME(NiezgodnyTypSurowca));
	str.addClass(OgolnyWyjatek::toString());
	return str.toString();
}