#include "ZmianaPotegowa.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"
#include "..\definicjeWezlowXML.h"

ZmianaPotegowa::ZmianaPotegowa( TiXmlElement * wezel )
	: wspolczynnik_(XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_PARAM, ATRYBUT_XML_IDENTYFIKATOR, "0x1" )),
	wykladnik_(XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_PARAM, ATRYBUT_XML_IDENTYFIKATOR, "0x2" ))
{
}

ZmianaPotegowa::~ZmianaPotegowa(void)
{
}

ZmianaInterfejs* ZmianaPotegowa::TworzZmianaPotegowa( TiXmlElement* wezel ){
	return new ZmianaPotegowa(wezel);
}

long double ZmianaPotegowa::policzWartosc(long double wartosc, int poziom, int identyfikatorPlanety) const{
	return wartosc * wspolczynnik_.pobierzWspolczynnik() * pow( static_cast<long double>(poziom), wykladnik_.pobierzWspolczynnik() );
}

ZmianaPotegowa* ZmianaPotegowa::Kopia()const{
	return new ZmianaPotegowa(*this);
}

bool ZmianaPotegowa::RejestrujZmianaPotegowa( ZmianaFabryka &fabryka ){
	return fabryka.rejestracjaZmiany( identyfikator_, ZmianaPotegowa::TworzZmianaPotegowa );
}

std::string ZmianaPotegowa::napis()const{
	Logger str(NAZWAKLASY(ZmianaPotegowa));
	str.dodajPole( "wspolczynnik", wspolczynnik_ );
	str.dodajPole( "wykladnik", wykladnik_ );
	return str.napis();
}
