#include "ZmianaPotegowa.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"
#include "..\definicjeWezlowXML.h"

ZmianaPotegowa::ZmianaPotegowa( TiXmlElement * wezel ) throw(int)
	: wspolczynnik_(XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_PARAM, ATRYBUT_XML_IDENTYFIKATOR, "1" )),
	wykladnik_(XmlBO::ZnajdzWezelJezeli<NOTHROW>( wezel, WEZEL_XML_PARAM, ATRYBUT_XML_IDENTYFIKATOR, "2" ))
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

string ZmianaPotegowa::toString()const{
	Logger str(CLASSNAME(ZmianaPotegowa));
	str.addField( "wspolczynnik", wspolczynnik_ );
	str.addField( "wykladnik", wykladnik_ );
	return str.toString();
}
