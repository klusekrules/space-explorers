#include "NiepoprawnaIloscObiektow.h"
#include "Logger.h"

NiepoprawnaIloscObiektow::NiepoprawnaIloscObiektow( const Tekst& tPlik, const IdType& iLinia, const Ilosc& ilosc )
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
	return OgolnyWyjatek::generujKomunikat() + Tekst("Ilosc:") +  i.Ilosc::toString() + Tekst("\n");
}

string NiepoprawnaIloscObiektow::toString() const{
	Logger str(LogNiepoprawnaIloscObiektow::className());	
	str.addClass(OgolnyWyjatek::toString());
	str.addField("Ilosc",i);
	return str.toString();
}
	