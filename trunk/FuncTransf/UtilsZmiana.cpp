#include "UtilsZmiana.h"


void UtilsZmiana::generujWyjatekBleduStruktury( TiXmlElement* wezel )
{
	std::string komunikat("Wczytywanie zmiany nie powiod�o si�. Wezel: ");
	komunikat << *wezel;
	throw std::exception(komunikat.c_str());
}
