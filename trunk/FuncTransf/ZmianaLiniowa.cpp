#include "ZmianaLiniowa.h"
#include "..\Logger\Logger.h"
#include "ZmianaFabryka.h"
#include "..\XmlBO.h"
#include "..\definicjeWezlowXML.h"

ZmianaLiniowa::ZmianaLiniowa( TiXmlElement* e )
	: parametr(XmlBO::ZnajdzWezelJezeli<NOTHROW>(e,WEZEL_XML_PARAM,ATRYBUT_XML_IDENTYFIKATOR,"0"))
{
}

ZmianaLiniowa::~ZmianaLiniowa(void)
{
}

long double ZmianaLiniowa::value(const long double& d, const int& p, const int&) const{
	return d * parametr.pobierzWspolczynnik() * p;
}

ZmianaLiniowa* ZmianaLiniowa::Kopia()const{
	return new ZmianaLiniowa(*this);
}

bool ZmianaLiniowa::RejestrujZmianaLiniowa(  ZmianaFabryka &ref ){
	return ref.RejestracjaZmiany(idKlasy,ZmianaLiniowa::TworzZmianaLiniowa);
}

string ZmianaLiniowa::toString()const{
	Logger str(CLASSNAME(ZmianaLiniowa));
	str.addField("Parametr",parametr);
	return str.toString();
}