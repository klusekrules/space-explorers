#include "Utils.h"
#include "Aplikacja.h"
#include "WyjatekParseraXML.h"

shared_ptr<ZmianaInterfejs> Utils::TworzZmiane( TiXmlElement* wezel ){
	if(!wezel)
		return nullptr;
	auto zmiana = Aplikacja::pobierzInstancje().pobierzGre().pobierzFabrykeZmian().Tworz(wezel);
	if(!zmiana)
		generujWyjatekBleduStruktury(EXCEPTION_PLACE,wezel);
	return zmiana;
}

void Utils::generujWyjatekBleduStruktury( const Tekst& plik, const Ilosc& linia, TiXmlElement* wezel )
{
	std::string komunikat("B³¹d struktry pliku xml. Niepoprawny wêze³: ");
	komunikat << *wezel;
	throw WyjatekParseraXML(plik,linia,exception(komunikat.c_str()),Tekst("B³¹d struktry pliku xml."));
}
