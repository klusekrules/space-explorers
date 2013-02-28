#include "WyjatekSTL.h"
#include "Logger.h"

WyjatekSTL::WyjatekSTL( const Tekst& tPlik, const IdType& iLinia )
	: OgolnyWyjatek(tPlik, iLinia,idWyjatekSTL,tytulWyjatekSTL,trescWyjatekSTL)
{
}

WyjatekSTL::~WyjatekSTL(){
}

WyjatekSTL::WyjatekSTL( const Tekst& tPlik, const IdType& iLinia, const Tekst& str , const std::exception& e )
	: OgolnyWyjatek(tPlik, iLinia,idWyjatekSTL , tytulWyjatekSTL ,str), powod(e.what())
{
}

WyjatekSTL::WyjatekSTL( const Tekst& tPlik, const IdType& iLinia, const std::exception& e )
	: OgolnyWyjatek(tPlik, iLinia,idWyjatekSTL , tytulWyjatekSTL ,trescWyjatekSTL), powod(e.what())
{
}

WyjatekSTL::WyjatekSTL( const WyjatekSTL& e )
	: OgolnyWyjatek(e), powod(e.powod)
{
}

Tekst WyjatekSTL::getPowod() const{
	return powod;
}

void WyjatekSTL::setPowod( const Tekst& powod ){
	this->powod = powod;
}

Tekst WyjatekSTL::generujKomunikat()const {
	return OgolnyWyjatek::generujKomunikat() + powod + Tekst("\n");
}

string WyjatekSTL::toString() const{
	Logger str(LogWyjSTL::className());	
	str.addClass(OgolnyWyjatek::toString());
	str.addField("Powod",powod);
	return str.toString();
}