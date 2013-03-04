#include "NiepoprawneParametryFunkcji.h"
#include "Logger.h"


NiepoprawneParametryFunkcji::~NiepoprawneParametryFunkcji(){
}

Tekst NiepoprawneParametryFunkcji::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("Lista parametrów:\n")  + parametry + Tekst("\n");
}

Tekst NiepoprawneParametryFunkcji::getFuncName() const{
	return parametry;
}

void NiepoprawneParametryFunkcji::setFuncName ( const Tekst& wwTresc ){
	parametry = wwTresc;
}

string NiepoprawneParametryFunkcji::toString() const{
	Logger str(LogNiepoprawneParametryFunkcji::className());
	str.addClass(OgolnyWyjatek::toString());
	str.addField("Parametry funkcji",parametry);
	return str.toString();
}
