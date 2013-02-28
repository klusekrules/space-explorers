#include "NiepoprawneParametryFunkcji.h"
#include "Logger.h"

NiepoprawneParametryFunkcji::NiepoprawneParametryFunkcji( const Tekst& tPlik, const IdType& iLinia, const Tekst& tFuncName )
	: OgolnyWyjatek( tPlik, iLinia, idNiepoprawneParametryFunkcji, tytulNiepoprawneParametryFunkcji, trescNiepoprawneParametryFunkcji ), funcName( tFuncName )
{
}

NiepoprawneParametryFunkcji::~NiepoprawneParametryFunkcji(void){
}

Tekst NiepoprawneParametryFunkcji::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("Funkcja:")  + funcName + Tekst("\n");
}

Tekst NiepoprawneParametryFunkcji::getFuncName() const{
	return funcName;
}

void NiepoprawneParametryFunkcji::setFuncName ( const Tekst& wwTresc ){
	funcName = wwTresc;
}

string NiepoprawneParametryFunkcji::toString() const{
	Logger str(LogNiepoprawneParametryFunkcji::className());
	str.addClass(OgolnyWyjatek::toString());
	str.addField("Nazwa Funkcji",funcName);
	return str.toString();
}
