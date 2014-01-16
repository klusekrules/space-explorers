#include "ZmianaLiniowa.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"
#include "..\definicjeWezlowXML.h"

ZmianaLiniowa::ZmianaLiniowa( tinyxml2::XMLElement* wezel )
	: parametr_(XmlBO::ZnajdzWezel<NOTHROW>( wezel, WEZEL_XML_PARAM ))
{
}

long double ZmianaLiniowa::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const{
	return wartosc * parametr_.pobierzWspolczynnik() * poziom;
}

ZmianaLiniowa* ZmianaLiniowa::Kopia()const{
	return new ZmianaLiniowa(*this);
}

bool ZmianaLiniowa::RejestrujZmianaLiniowa(  ZmianaFabryka &fabryka ){
	return fabryka.rejestracjaZmiany(identyfikator_,ZmianaLiniowa::TworzZmianaLiniowa);
}

ZmianaInterfejs* ZmianaLiniowa::TworzZmianaLiniowa( tinyxml2::XMLElement* wezel ){
	return new ZmianaLiniowa(wezel);
}

std::string&& ZmianaLiniowa::napis()const{
	Logger str(NAZWAKLASY(ZmianaLiniowa));
	str.dodajPole("Parametr",parametr_);
	return str.napis();
}
