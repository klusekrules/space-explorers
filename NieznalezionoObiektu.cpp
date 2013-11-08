#include "NieznalezionoObiektu.h"
#include "Logger.h"

NieznalezionoObiektu::NieznalezionoObiektu(const Tekst& tPlik, const Ilosc& iLinia, const Tekst& tNazwa)
	: OgolnyWyjatek( tPlik, iLinia, idNieznalezionoObiektu, tytulNieznalezionoObiektu, trescNieznalezionoObiektu ) , identyfikator( tNazwa )
{
}

NieznalezionoObiektu::~NieznalezionoObiektu(){
}

const Tekst& NieznalezionoObiektu::getIdentyfikator() const{
	return identyfikator;
}

void NieznalezionoObiektu::setIdentyfikator( const Tekst& nazwa ){
	this->identyfikator = nazwa;
}

Tekst NieznalezionoObiektu::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("Identyfikator:") +  identyfikator + Tekst("\n");
}


std::string NieznalezionoObiektu::napis() const{
	Logger str(NAZWAKLASY(NieznalezionoObiektu));	
	str.dodajKlase(OgolnyWyjatek::napis());
	str.dodajPole("Identyfikator",identyfikator);
	return str.napis();
}