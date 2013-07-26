#include "Utils.h"
#include "Aplikacja.h"

shared_ptr<ZmianaInterfejs> Utils::TworzZmiane( TiXmlElement* e ){
	return Aplikacja::getInstance().getGra().pobierzFabrykeZmian().Tworz(e);
}