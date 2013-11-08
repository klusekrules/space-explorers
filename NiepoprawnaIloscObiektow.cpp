#include "NiepoprawnaIloscObiektow.h"
#include "Logger.h"

NiepoprawnaIloscObiektow::NiepoprawnaIloscObiektow( const Tekst& tPlik, const Ilosc& iLinia, const Ilosc& ilosc )
	: OgolnyWyjatek( tPlik, iLinia, idNiepoprawnaIloscObiektow , tytulNiepoprawnaIloscObiektow, trescNiepoprawnaIloscObiektow ), i(ilosc)
{
}

NiepoprawnaIloscObiektow::~NiepoprawnaIloscObiektow(void){
}

const Ilosc& NiepoprawnaIloscObiektow::getIlosc() const{
	return i;
}

void NiepoprawnaIloscObiektow::setIlosc( const Ilosc& ilosc ){
	i = ilosc;
}

Tekst NiepoprawnaIloscObiektow::generujKomunikat() const{
	return OgolnyWyjatek::generujKomunikat() + Tekst("Ilosc:") +  i.Ilosc::napis() + Tekst("\n");
}

std::string NiepoprawnaIloscObiektow::napis() const{
	Logger str(NAZWAKLASY(NiepoprawnaIloscObiektow));	
	str.dodajKlase(OgolnyWyjatek::napis());
	str.dodajPole("Ilosc",i);
	return str.napis();
}
	