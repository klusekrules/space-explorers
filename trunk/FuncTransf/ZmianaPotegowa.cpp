#include "ZmianaPotegowa.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"
#include "..\definicjeWezlowXML.h"

ZmianaPotegowa::ZmianaPotegowa( TiXmlElement * e ) throw(int)
	: wspolczynnik(XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,WEZEL_XML_PARAM,ATRYBUT_XML_IDENTYFIKATOR,"1")), wykladnik(XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,WEZEL_XML_PARAM,ATRYBUT_XML_IDENTYFIKATOR,"2"))
{
}

ZmianaPotegowa::~ZmianaPotegowa(void)
{
}

long double ZmianaPotegowa::value(const long double& d, const int& p, const int&) const{
	return d * wspolczynnik.pobierzWspolczynnik() * pow(static_cast<long double>(p),wykladnik.pobierzWspolczynnik());
}

ZmianaPotegowa* ZmianaPotegowa::Kopia()const{
	return new ZmianaPotegowa(*this);
}

bool ZmianaPotegowa::RejestrujZmianaPotegowa( ZmianaFabryka &ref ){
	return ref.RejestracjaZmiany(idKlasy,ZmianaPotegowa::TworzZmianaPotegowa);
}

string ZmianaPotegowa::toString()const{
	Logger str(CLASSNAME(ZmianaPotegowa));
	str.addField("wspolczynnik",wspolczynnik);
	str.addField("wykladnik",wykladnik);
	return str.toString();
}