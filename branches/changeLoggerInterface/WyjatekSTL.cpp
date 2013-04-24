#include "WyjatekSTL.h"
#include "Logger.h"


WyjatekSTL::~WyjatekSTL(){
}

WyjatekSTL::WyjatekSTL( const Tekst& tPlik, const IdType& iLinia, const std::exception& e, const Tekst& str )
	: OgolnyWyjatek(tPlik, iLinia,idWyjatekSTL , tytulWyjatekSTL ,str.isEmpty() ? trescWyjatekSTL : str), powod(e.what())
{
}

WyjatekSTL::WyjatekSTL( const WyjatekSTL& e )
	: OgolnyWyjatek(e), powod(e.powod)
{
}

const Tekst& WyjatekSTL::getPowod() const{
	return powod;
}

void WyjatekSTL::setPowod( const Tekst& powod ){
	this->powod = powod;
}

Tekst WyjatekSTL::generujKomunikat()const {
	return OgolnyWyjatek::generujKomunikat() + powod + Tekst("\n");
}

string WyjatekSTL::toString() const{
	Logger str(CLASSNAME(WyjatekSTL));	
	str.addClass(OgolnyWyjatek::toString());
	str.addField("Powod",powod);
	return str.toString();
}