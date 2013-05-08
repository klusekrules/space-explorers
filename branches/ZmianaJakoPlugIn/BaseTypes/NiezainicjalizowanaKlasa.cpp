#include "NiezainicjalizowanaKlasa.h"
#include "../Logger/Logger.h"

NiezainicjalizowanaKlasa::NiezainicjalizowanaKlasa(const Tekst& tPlik, const IdType& iLinia, const Tekst& tNazwa)
	: OgolnyWyjatek( tPlik, iLinia, idNiezainicjalizowanaKlasa, tytulNiezainicjalizowanaKlasa, trescNiezainicjalizowanaKlasa ) , nazwaKlasy( tNazwa )
{
}

NiezainicjalizowanaKlasa::~NiezainicjalizowanaKlasa(){
}

const Tekst& NiezainicjalizowanaKlasa::getNazwaKlasy() const{
	return nazwaKlasy;
}

void NiezainicjalizowanaKlasa::setNazwaKlasy( const Tekst& nazwa ){
	this->nazwaKlasy = nazwa;
}

Tekst NiezainicjalizowanaKlasa::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("Nazwa klasy:") +  nazwaKlasy + Tekst("\n");
}


string NiezainicjalizowanaKlasa::toString() const{
	Logger str(CLASSNAME(NiezainicjalizowanaKlasa));	
	str.addClass(OgolnyWyjatek::toString());
	str.addField("Nazwa klasy",nazwaKlasy);
	return str.toString();
}