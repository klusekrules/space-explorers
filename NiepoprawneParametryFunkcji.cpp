#include "NiepoprawneParametryFunkcji.h"
#include "Logger.h"


NiepoprawneParametryFunkcji::~NiepoprawneParametryFunkcji(){
}

Tekst NiepoprawneParametryFunkcji::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("Lista parametr�w:\n")  + parametry + Tekst("\n");
}

const Tekst& NiepoprawneParametryFunkcji::getParametry() const{
	return parametry;
}

void NiepoprawneParametryFunkcji::setParametry ( const Tekst& wwTresc ){
	parametry = wwTresc;
}

string NiepoprawneParametryFunkcji::napis() const{
	Logger str(NAZWAKLASY(NiepoprawneParametryFunkcji));
	str.dodajKlase(OgolnyWyjatek::napis());
	str.dodajPole("Parametry funkcji",parametry);
	return str.napis();
}
