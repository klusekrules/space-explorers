#include "UtilsZmiana.h"

void UtilsZmiana::generujWyjatekBleduStruktury( tinyxml2::XMLElement* wezel )
{
	std::string komunikat("Wczytywanie zmiany nie powiod³o siê. Wezel: ");
	tinyxml2::XMLPrinter printer;
	wezel->Accept( &printer );
	komunikat.append( printer.CStr() );
	throw std::exception(komunikat.c_str());
}
