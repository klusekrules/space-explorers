#include "NieznalezionoObiektu.h"
#include "Logger.h"

NieznalezionoObiektu::NieznalezionoObiektu(const Tekst& tPlik, const IdType& iLinia, const Tekst& tNazwa)
	: OgolnyWyjatek( tPlik, iLinia, idNieznalezionoObiektu, tytulNieznalezionoObiektu, trescNieznalezionoObiektu ) , identyfikator( tNazwa )
{
}

NieznalezionoObiektu::~NieznalezionoObiektu(){
}

Tekst NieznalezionoObiektu::getIdentyfikator() const{
	return identyfikator;
}

void NieznalezionoObiektu::setIdentyfikator( const Tekst& nazwa ){
	this->identyfikator = nazwa;
}

Tekst NieznalezionoObiektu::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("Identyfikator:") +  identyfikator + Tekst("\n");
}


string NieznalezionoObiektu::toString() const{
	Logger str(LogNieznalezionoObiektu::className());	
	str.addClass(OgolnyWyjatek::toString());
	str.addField("Identyfikator",identyfikator);
	return str.toString();
}