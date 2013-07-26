#include "Utils.h"
#include "Aplikacja.h"

shared_ptr<ZmianaInterfejs> Utils::TworzZmiane( TiXmlElement* e ){
	return Aplikacja::pobierzInstancje().pobierzGre().pobierzFabrykeZmian().Tworz(e);
}